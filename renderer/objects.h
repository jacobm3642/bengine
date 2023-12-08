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

R_Polygon *init_polygon();
void test();
void add_triangle(R_Polygon *polygon, float *vertices);