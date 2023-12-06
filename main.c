#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include "renderer/objects.h"

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>

#pragma comment(lib, "glew32.lib")
// Function to handle window messages

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_CREATE:
            return 0;

        case WM_CLOSE:
            PostQuitMessage(0);
            return 0;

        case WM_SIZE:
            glViewport(0, 0, LOWORD(lParam), HIWORD(lParam));
            return 0;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
}

// Function to set up OpenGL
void SetupOpenGL(HWND hWnd, HDC* hDC, HGLRC* hRC) {
    PIXELFORMATDESCRIPTOR pfd;
    int format;

    // Set pixel format
    ZeroMemory(&pfd, sizeof(pfd));
    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    *hDC = GetDC(hWnd);
    format = ChoosePixelFormat(*hDC, &pfd);
    SetPixelFormat(*hDC, format, &pfd);

    // Create and enable the OpenGL rendering context
    *hRC = wglCreateContext(*hDC);
    wglMakeCurrent(*hDC, *hRC);
}

// Function to initialize OpenGL
void InitOpenGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
}

// Function to render the scene
void RenderScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_POLYGON);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-0.6, -0.6);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(0.6, -0.6);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.6, 0.6);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(-0.6, 0.6);
    glEnd();

    glFlush();
}

int main() {
    // Register the window class
    WNDCLASS wc = { CS_BYTEALIGNCLIENT, (WNDPROC)WndProc, 0, 0, GetModuleHandle(NULL),
                    LoadIcon(NULL, IDI_APPLICATION), LoadCursor(NULL, IDC_ARROW),
                    (HBRUSH)GetStockObject(BLACK_BRUSH), NULL, "OpenGL" };
    RegisterClass(&wc);

    // Create the window
    HWND hWnd = CreateWindow("OpenGL", "OpenGL Window", WS_OVERLAPPEDWINDOW,
        100, 100, 800, 600, NULL, NULL, GetModuleHandle(NULL), NULL);

    HDC hDC;
    HGLRC hRC;

    // Set up OpenGL
    SetupOpenGL(hWnd, &hDC, &hRC);

    // Initialize OpenGL
    InitOpenGL();

    // Display the window
    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    // Main message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        RenderScene();
        SwapBuffers(hDC);
    }

    // Clean up and exit
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hWnd, hDC);
    DestroyWindow(hWnd);

    return msg.wParam;
}

#elif defined(__linux__) 

#include<X11/X.h>
#include<X11/Xlib.h>
#include<GL/glx.h>
#include<GL/glu.h>


Display                 *dpy;
Window                  root;
GLint                   att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
XVisualInfo             *vi;
Colormap                cmap;
XSetWindowAttributes    swa;
Window                  win;
GLXContext              glc;
XWindowAttributes       gwa;
XEvent                  xev;

int main(int argc, char *argv[]) {


 	// this creates a connection to a display server
 	dpy = XOpenDisplay(NULL);
	
 	// this checks if the server has made a connection
 	if(dpy == NULL) {
 		printf("\n\tcannot connect to X server\n\n");
 	    exit(0);
 	}
	
 	// this gets a root window for the display pass into it
 	root = DefaultRootWindow(dpy);

 	// seems to create the visual that i want 
 	vi = glXChooseVisual(dpy, 0, att);

 	// checks if the visual worked and if it did makes a hex output
 	if(vi == NULL) {
		printf("\n\tno appropriate visual found\n\n");
 	    exit(0);
 	} 
 	else {
		printf("\n\tvisual %p selected\n", (void *)vi->visualid); /* %p creates hexadecimal output like in glxinfo */
 	}

	// creates a colormap but doesint allocte any colors
 	cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);

 	swa.colormap = cmap;
 	swa.event_mask = ExposureMask | KeyPressMask;
	
 	win = XCreateWindow(dpy, root, 0, 0, 600, 600, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);

 	XMapWindow(dpy, win);
 	XStoreName(dpy, win, "Empty Window");
 
 	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
 	glXMakeCurrent(dpy, win, glc);
 
	glEnable(GL_DEPTH_TEST); 
    
    hello();
    
	while(1){
    	while (XPending(dpy) > 0) {
    	    XNextEvent(dpy, &xev);

    	    if (xev.type == Expose) {
    	        XGetWindowAttributes(dpy, win, &gwa);
    	        glViewport(0, 0, gwa.width, gwa.height);
    	        glXSwapBuffers(dpy, win);
    	    } else if (xev.type == KeyPress) {
    	        KeySym key = XLookupKeysym(&xev.xkey, 0);

    	        switch (key) {
    	            case XK_Escape:
    	                glXMakeCurrent(dpy, None, NULL);
    	                glXDestroyContext(dpy, glc);
    	                XDestroyWindow(dpy, win);
    	                XCloseDisplay(dpy);
    	                exit(0);
    	                break;
    	        }
    	    }
    	}
	}
}

#else
    #error "Unsupported operating system"
#endif