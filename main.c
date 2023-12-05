#include <stdio.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
            case WM_DESTROY:
                PostQuitMessage(0);
                return 0;

            default:
                return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    int main() {
        // Register the window class
        const char CLASS_NAME[] = "EmptyWindowClass";

        WNDCLASS wc = {0};
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = GetModuleHandle(NULL);
        wc.lpszClassName = CLASS_NAME;

        RegisterClass(&wc);

        // Create the window
        HWND hwnd = CreateWindowEx(
            0,                    // Optional window styles
            CLASS_NAME,           // Window class
            "Empty Window",       // Window text
            WS_OVERLAPPEDWINDOW,  // Window style

            // Size and position
            CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,

            NULL,      // Parent window
            NULL,      // Menu
            GetModuleHandle(NULL), // Instance handle
            NULL       // Additional application data
        );

        if (hwnd == NULL) {
            return 1;
        }

        ShowWindow(hwnd, SW_SHOWDEFAULT);

        // Main message loop
        MSG msg = {0};
        while (GetMessage(&msg, NULL, 0, 0)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        return 0;
    }
#elif defined(__linux__) 
    #include<GL/glew.h>
    #include<X11/X.h>
    #include<X11/Xlib.h>
    #include<GL/gl.h>
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

        GLenum err = glewInit();
        if (GLEW_OK != err) {
            fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
            exit(1);
        }

        GLuint vertexBuffer;
        GLfloat vertices[] = {
            -0.5f, -0.5f, 0.0f,  // Bottom-left
            0.5f, -0.5f, 0.0f,   // Bottom-right
            0.0f, 0.5f, 0.0f     // Top
        };

        glGenBuffers(1, &vertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


        while(1){
            while (XPending(dpy) > 0) {
                XNextEvent(dpy, &xev);
                
                if (xev.type == Expose) {
                    glXMakeCurrent(dpy, win, glc);

                    XGetWindowAttributes(dpy, win, &gwa);
                    glViewport(0, 0, gwa.width, gwa.height);
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

                    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
                    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
                    glEnableVertexAttribArray(0);

                    glDrawArrays(GL_TRIANGLES, 0, 3);

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