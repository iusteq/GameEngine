#include <OGL3D/Graphics/OGraphicsEngine.h>
#include <glad/glad.h>
#include <glad/glad_wgl.h>
#include <assert.h>
#include <stdexcept>

OGraphicsEngine::OGraphicsEngine()
{
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.lpszClassName = L"OGL3DDummyWindow";
	wc.lpfnWndProc = DefWindowProc;

	auto classId = RegisterClassEx(&wc);
	assert(classId);

	auto dummyWindow = CreateWindowEx(NULL, MAKEINTATOM(classId), L"", WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, NULL, NULL);
	assert(dummyWindow);

	auto dummyDC = GetDC(dummyWindow);

	PIXELFORMATDESCRIPTOR pixelFormatDescription = {};
	pixelFormatDescription.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pixelFormatDescription.nVersion = 1;
	pixelFormatDescription.iPixelType = PFD_TYPE_RGBA;
	pixelFormatDescription.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
	pixelFormatDescription.cColorBits = 32;
	pixelFormatDescription.cAlphaBits = 8;
	pixelFormatDescription.cDepthBits = 24;
	pixelFormatDescription.cStencilBits = 8;
	pixelFormatDescription.iLayerType = PFD_MAIN_PLANE;

	auto pixelFormat = ChoosePixelFormat(dummyDC, &pixelFormatDescription);
	SetPixelFormat(dummyDC, pixelFormat, &pixelFormatDescription);

	auto dummyContext = wglCreateContext(dummyDC);
	assert(dummyContext);

	wglMakeCurrent(dummyDC,dummyContext);

	if (!gladLoadWGL(dummyDC))
		throw std::runtime_error("OGraphicsEngine - Error - gladLoadWGL failed");

	if (!gladLoadGL())
		throw std::runtime_error("OGraphicsEngine - Error - gladLoadGL failed");

	wglMakeCurrent(dummyDC, 0);
	wglDeleteContext(dummyContext);
	ReleaseDC(dummyWindow, dummyDC);
	DestroyWindow(dummyWindow);
}

OGraphicsEngine::~OGraphicsEngine()
{
}
