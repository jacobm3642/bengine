#include "objects.h"
#include <stdlib.h>
#include <stdio.h>

Polygon *init_polygon() {
    Polygon *new_polygon;
    new_polygon = malloc(sizeof(Polygon));
    for (int i; i < 255; i++){
        new_polygon->vertexs[i] = 0;
    }
    for (int i; i < 255; i++){
        new_polygon->indexs[i] = 0;
    }
    return new_polygon;
}