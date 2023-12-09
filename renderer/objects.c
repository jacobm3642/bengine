// objects.c

#if defined(_WIN32) || defined(_WIN64)
  #define EXPORT __declspec(dllexport)
#else
  #define EXPORT __attribute__((visibility("default")))
#endif

#include "objects.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

EXPORT R_Polygon *init_polygon() {
    R_Polygon *new_polygon;
    new_polygon = malloc(sizeof(R_Polygon));
    for (int i=0; i < 255; i++){
        new_polygon->vertices[i] = 0;
        new_polygon->indices[i] = 0;
    }
    new_polygon->vertices[0]='\0';
    new_polygon->indices[0]='\0';
    return new_polygon;
}

EXPORT void add_triangle(R_Polygon *polygon, float *vertices) {
    int i;
    for (i = 0; i < 255 && polygon->vertices[i] != '\0'; i++) {
    }
    polygon->vertices[i] = vertices[0];
    polygon->vertices[i + 1] = vertices[1];
    polygon->vertices[i + 2] = vertices[2];
    polygon->vertices[i + 3] = '\0';
}

EXPORT void test(){
    // Initialize a polygon
    R_Polygon *polygon = init_polygon();

    // Define vertices for a triangle
    float triangleVertices[] = {1.0, 2.0, 3.0};

    // Add the triangle to the polygon
    add_triangle(polygon, triangleVertices);

    // Verify the result
    assert(polygon->vertices[0] == 1.0);
    assert(polygon->vertices[1] == 2.0);
    assert(polygon->vertices[2] == 3.0);
    assert(polygon->vertices[3] == '\0');

    // Clean up
    free(polygon);

    printf("Test case passed!\n");
}