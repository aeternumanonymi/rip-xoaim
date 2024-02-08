// overlay.cpp

#include "overlay.hpp"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK window_procedure(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
    if (ImGui_ImplWin32_WndProcHandler(window, message, w_param, l_param))
    {
        return 0L;
    }

    if (message == WM_DESTROY)
    {
        PostQuitMessage(0);
        return 0L;
    }

    return DefWindowProc(window, message, w_param, l_param);
}

bool c_overlay::initialize(HINSTANCE instance, INT cmd_show)
{
    m_wc.cbSize = sizeof(WNDCLASSEXW);
    m_wc.style = CS_HREDRAW | CS_VREDRAW;
    m_wc.lpfnWndProc = window_procedure;
    m_wc.hInstance = instance;

    wchar_t class_name[128] = {'\0'};
    util::convert_string(xors("XOAim - Debug Overlay"), class_name);
    m_wc.lpszClassName = class_name;
    RegisterClassExW(&m_wc);
    m_window = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_LAYERED, m_wc.lpszClassName, class_name, WS_POPUP, 0, 0, 1920, 1080, nullptr, nullptr, m_wc.hInstance, nullptr);
    SetLayeredWindowAttributes(m_window, RGB(0, 0, 0), BYTE(255), LWA_ALPHA);

    RECT client_area = {};
    GetClientRect(m_window, &client_area);

    RECT window_area = {};
    GetWindowRect(m_window, &window_area);

    POINT diff = {};
    ClientToScreen(m_window, &diff);

    const MARGINS margins{
        window_area.left + (diff.x - window_area.left),
        window_area.top + (diff.x - window_area.top),
        client_area.right,
        client_area.bottom};

    DwmExtendFrameIntoClientArea(m_window, &margins);

    DXGI_SWAP_CHAIN_DESC sd = {};
    sd.BufferDesc.RefreshRate.Numerator = 60U;
    sd.BufferDesc.RefreshRate.Denominator = 1U;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.SampleDesc.Count = 1U;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.BufferCount = 2U;
    sd.OutputWindow = m_window;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    constexpr D3D_FEATURE_LEVEL levels[2]{D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0};
    D3D_FEATURE_LEVEL level{};
    D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0U, levels, 2U, D3D11_SDK_VERSION, &sd, &m_swap_chain, &m_device, &level, &m_device_context);

    ID3D11Texture2D *back_buffer{nullptr};
    m_swap_chain->GetBuffer(0U, IID_PPV_ARGS(&back_buffer));
    if (!back_buffer)
    {
        return false;
    }

    m_device->CreateRenderTargetView(back_buffer, nullptr, &m_render_target_view);
    back_buffer->Release();

    ShowWindow(m_window, cmd_show);
    UpdateWindow(m_window);

    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplWin32_Init(m_window);
    ImGui_ImplDX11_Init(m_device, m_device_context);

    return true;
}

void c_overlay::execute()
{
    MSG msg;
    while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        if (msg.message == WM_QUIT)
        {
            break;
        }
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();

    ImGui::NewFrame();
    draw();
    ImGui::Render();

    constexpr float color[4]{0.f, 0.f, 0.f, 0.f};
    m_device_context->OMSetRenderTargets(1U, &m_render_target_view, nullptr);
    m_device_context->ClearRenderTargetView(m_render_target_view, color);

    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    m_swap_chain->Present(1U, 0U);
}

void c_overlay::draw()
{
    ImDrawList *draw_list = ImGui::GetBackgroundDrawList();

    for (auto entity : g_entities.m_entities)
    {
        if (!entity.life_state || entity.health <= 0 || entity.health > 100)
        {
            continue;
        }

        // Draw visibility
        math::vec2 screen_position;
        if (g_entities.world_to_screen(entity.head_bone, &screen_position))
        {
            auto start = g_entities.m_local_player.origin;
            start.z += 70.f;

            if (g_vischeck.is_visible(start, entity.head_bone))
            {
                draw_list->AddCircle(ImVec2(screen_position.x, screen_position.y), 6, ImColor(60, 255, 0), 32, 1.0f);
            }
            else
            {
                draw_list->AddCircle(ImVec2(screen_position.x, screen_position.y), 6, ImColor(255, 0, 0), 32, 1.0f);
            }
        }
    }

    for (auto target : g_aimbot.m_targets)
    {
        math::vec2 label_position;
        auto bone_position = target.entity.head_bone;

        bone_position.x -= 18.f;
        bone_position.z += 10.f;

        if (g_entities.world_to_screen(bone_position, &label_position))
        {
            char buf[666];
            sprintf(buf, "visible for %dms", target.visible_for_ms);
            draw_list->AddText(ImVec2(label_position.x, label_position.y + 10.f), ImColor(60, 255, 0), buf);
        }
    }
}

void c_overlay::terminate()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();

    ImGui::DestroyContext();

    if (m_swap_chain)
    {
        m_swap_chain->Release();
    }

    if (m_device_context)
    {
        m_device_context->Release();
    }

    if (m_device)
    {
        m_device->Release();
    }

    if (m_render_target_view)
    {
        m_render_target_view->Release();
    }

    DestroyWindow(m_window);
    UnregisterClassW(m_wc.lpszClassName, m_wc.hInstance);
}