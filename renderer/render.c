#if defined(_WIN32) || defined(_WIN64)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

#include "render.h"
#include "objects.h"
#include <stdlib.h>
#include <stdio.h>

EXPORT void init_opengl() {

}

EXPORT char *shader_parcer(char *name) {
    return name;
}

EXPORT void render_triangle(R_Polygon *polygon) {

}