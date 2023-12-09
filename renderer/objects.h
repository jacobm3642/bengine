#ifndef OBJECTS_H
#define OBJECTS_H

#ifdef _WIN32
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT __attribute__((visibility("default")))
#endif

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

EXPORT R_Polygon *init_polygon();
EXPORT void add_triangle(R_Polygon* polygon, float* vertices);
EXPORT void test(void);

#endif // OBJECTS_H
