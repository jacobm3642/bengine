// objects.h
#ifndef OBJECTS_H
#define OBJECTS_H

typedef struct R_Color {
    char r;
    char g;
    char b;
} R_Color;

typedef struct R_Polygon {
    float vertices[255];
    char indices[255];
    R_Color color;
} R_Polygon;

#ifdef BUILDING_DLL
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT __declspec(dllimport)
#endif

DLL_EXPORT R_Polygon *init_polygon();
DLL_EXPORT void test();
DLL_EXPORT void add_triangle(R_Polygon *polygon, float *vertices);

#endif // OBJECTS_H
