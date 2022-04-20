#pragma once

typedef struct Vec2f {
    float x;
    float y;
} Vec2f;

typedef struct Vec3f {
    float x;
    float y;
    float z;
} Vec3f;

typedef struct Vec4f {
    float x;
    float y;
    float z;
    float w;
} Vec4f;

// float lerpf(float a, float b, float t)
// {
//     return a + (b - a) * t;
// }