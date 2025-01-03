#ifndef COMMON_H
#define COMMON_H

typedef struct s_vec2 {
    float x;
    float y;
} Vector2;

typedef struct s_vec2int32 {
    int x;
    int y;
} Vector2Int;

typedef struct s_vec2int16 {
    short x;
    short y;
} Vector2Short;

typedef struct s_vec3 {
    float x;
    float y;
    float z;
} Vector3, ColorRGB;

typedef struct s_vec3int {
    int x;
    int y;
    int z;
} Vector3Int;


#define Vector2Int_Print(Vec2) printf("( %i, %i )", Vec2.x, Vec2.y);

#define crash(msg) ({\
    printf(msg);\
    int die = 0 / 0;\
    })

#define clrscr() printf("\x1b[1;1H\x1b[2J");

#endif //COMMON_H
