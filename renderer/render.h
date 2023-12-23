#ifndef RENDER_H
#define RENDER_H

#include "objects.h"

#if defined(_WIN32) || defined(_WIN64)
    #define EXPORT __declspec(dllexport)
#else
    #define EXPORT __attribute__((visibility("default")))
#endif

EXPORT void init_opengl();
EXPORT char *shader_parcer(char *name);
EXPORT void render_triangle(R_Polygon *polygon);

#endif