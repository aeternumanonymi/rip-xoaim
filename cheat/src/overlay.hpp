#ifndef OVERLAY_HPP
#define OVERLAY_HPP

#include <d3d11.h>
#include <dwmapi.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>
#include <util.hpp>

#include "entities.hpp"
#include "vischeck.hpp"
#include "aimbot.hpp"

extern c_aimbot g_aimbot;

class c_overlay
{
public:
    c_overlay() = default;
    ~c_overlay() = default;

public:
    bool initialize(HINSTANCE instance, INT cmd_show);
    void execute();
    void draw();
    void terminate();

private:
    ID3D11Device *m_device = nullptr;
    IDXGISwapChain *m_swap_chain = nullptr;
    ID3D11DeviceContext *m_device_context = nullptr;
    ID3D11RenderTargetView *m_render_target_view = nullptr;
    WNDCLASSEXW m_wc = {};
    HWND m_window = nullptr;
};

#endif