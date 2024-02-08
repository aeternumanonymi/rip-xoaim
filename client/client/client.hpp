#include <Windows.h>
#include <string>

#include <AppCore/AppCore.h>
#include <AppCore/App.h>
#include <AppCore/Window.h>
#include <AppCore/Overlay.h>

#pragma comment(lib, "AppCore.lib")
#pragma comment(lib, "Ultralight.lib")
#pragma comment(lib, "UltralightCore.lib")
#pragma comment(lib, "WebCore.lib")

using namespace ultralight;

class Client : public WindowListener, public LoadListener,
    public ViewListener {
public:
    Client();
    virtual ~Client();

public:
    virtual void OnClose(Window* window) override;
    virtual void OnResize(Window* window, uint32_t width, uint32_t height) override;
    virtual void OnChangeCursor(View* caller, Cursor cursor) override;
    virtual void OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) override;
    
public:
    void Run();

private:
    void ResizeWindow(const int& width, const int& height);

private:
    void Authenticate(const JSObject& obj, const JSArgs& args);
    void OpenLinkInBrowser(const JSObject& obj, const JSArgs& args);
    void SetCurrentRoute(const std::string& route);
    void SetLoadingStatus(const std::string& status);

private:
    RefPtr<App> m_app;
    RefPtr<Window> m_window;
    RefPtr<Overlay> m_overlay;

private:
    HWND m_hwnd;

private:
    JSFunction m_setCurrentRoute;
    JSFunction m_setLoadingStatus;
};