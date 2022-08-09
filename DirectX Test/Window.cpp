#include "Window.h"

Window* window = NULL;
Window::Window()
{
};
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {

	switch (msg)
	{
	case WM_CREATE: // While window is created!
	{
		window->onCreate();
		break;
	}
	case WM_DESTROY: // While window is closed
	{
		window->onDestroy();
		::PostQuitMessage(0);
		break;
	}

	default:
		return ::DefWindowProc(hwnd, msg, wparam, lparam);
	}

	return NULL;
}
bool Window::init()
{

	WNDCLASSEX wc;
	wc.cbClsExtra = NULL;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.cbWndExtra = NULL;
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hIcon = LoadIcon(NULL, IDI_ERROR);
	wc.hIconSm = LoadIcon(NULL, IDI_ERROR);
	wc.hInstance = NULL;
	wc.lpszClassName = "MainWindowClass";
	wc.lpszMenuName = "";
	wc.style = NULL;
	wc.lpfnWndProc = &WndProc;

	if (!::RegisterClassEx(&wc))
		return false;



	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, "MainWindowClass", "DirectTest", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, NULL, NULL, NULL);

	if (!m_hwnd)
		return false;

	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	if (!window)
		window = this;

	m_is_run = true;
	return true;
}

bool Window::broadcast()
{

	MSG msg;

	while (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	window->onUpdate();


	Sleep(0);


	return true;
}

bool Window::release()
{
	if (::DestroyWindow(m_hwnd))
		return false;


	return true;
}
bool Window::isRun()
{
	return m_is_run;
}
void Window::onDestroy()
{
	m_is_run = false;
}
Window::~Window()
{
};