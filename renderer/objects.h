typedef struct Color {
    char r;
    char g;
    char b;
} Color;

typedef struct Polygon {
    float vertexs[255];
    char indexs[255];
    Color color;
} Polygon;

Polygon *init_polygon();

void hello();