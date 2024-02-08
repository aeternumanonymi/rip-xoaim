#include "client.hpp"

#define WINDOW_WIDTH    620
#define WINDOW_HEIGHT   350

Client::Client()
{
    m_app = App::Create();
    m_window = Window::Create(m_app->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT, false, kWindowFlags_Titled);
    m_window->MoveToCenter();

    m_window->SetTitle("XOAim - Counter-Strike 2");
    m_overlay = Overlay::Create(m_window.get(), WINDOW_WIDTH, WINDOW_HEIGHT, 0, 0);

    m_overlay->view()->LoadURL("file:///application/index.html#");

    m_window->set_listener(this);
    m_overlay->view()->set_view_listener(this);
    m_overlay->view()->set_load_listener(this);

    m_overlay->Focus();
    
    m_hwnd = reinterpret_cast<HWND>(m_window->native_handle());
}

Client::~Client() {}

void Client::OnClose(Window* window)
{
    m_app->Quit();
}

void Client::OnResize(Window* window, uint32_t width, uint32_t height)
{
    m_overlay->Resize(width, height);
}

void Client::OnChangeCursor(View* caller, Cursor cursor)
{
    m_window->SetCursor(cursor);
}
 
void Client::OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url)
{
    RefPtr<JSContext> context = caller->LockJSContext();
    SetJSContext(context->ctx());
    JSObject global = JSGlobalObject();

    global["authenticate"] = BindJSCallback(&Client::Authenticate);
    global["openLinkInBrowser"] = BindJSCallback(&Client::OpenLinkInBrowser);

    m_setCurrentRoute = global["setCurrentRoute"];
    m_setLoadingStatus = global["setLoadingStatus"];
}

void Client::Run()
{
    m_app->Run();
}

void Client::ResizeWindow(const int& width, const int& height)
{
    SetWindowPos(m_hwnd, NULL, 0, 0, width, height, SWP_SHOWWINDOW);
    OnResize(m_window.get(), width, height);
    m_window->MoveToCenter();
}

void Client::Authenticate(const JSObject& obj, const JSArgs& args)
{
	JSString argString = args[0];

	auto length = JSStringGetLength(argString);
    if (!length) {
        return;
    }

    auto buffer = (char*)malloc(length + 1);
    JSStringGetUTF8CString(argString, buffer, length + 1);
    if (buffer) {
        const auto credentials = std::string(buffer);
        SetCurrentRoute("loading");
        ResizeWindow(600, 200);
        SetLoadingStatus("Verifing your credentials...");
    }
}

void Client::OpenLinkInBrowser(const JSObject& obj, const JSArgs& args)
{
    JSString argString = args[0];

    auto length = JSStringGetLength(argString);
    if (!length) {
        return;
    }

    auto buffer = (char*)malloc(length + 1);
    JSStringGetUTF8CString(argString, buffer, length + 1);
    if (buffer) {
        const auto url = std::string(buffer);
        ShellExecuteA(0, 0, url.c_str(), 0, 0, SW_SHOW);
    }
}

void Client::SetCurrentRoute(const std::string& route)
{
    if (m_setCurrentRoute.IsValid())
    {
        m_setCurrentRoute({ route.c_str() });
    }
}

void Client::SetLoadingStatus(const std::string& status)
{
    if (m_setLoadingStatus.IsValid())
    {
        m_setLoadingStatus({ status.c_str() });
    }
}