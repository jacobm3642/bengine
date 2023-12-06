typedef struct R_Color {
    char r;
    char g;
    char b;
} R_Color;

typedef struct R_Polygon {
    float vertexs[255];
    char indexs[255];
    R_Color color;
} R_Polygon;

R_Polygon *init_polygon();

void hello();