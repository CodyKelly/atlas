//
// Created by hoy on 11/21/25.
//

#ifndef ATLAS_MATH_H
#define ATLAS_MATH_H

typedef struct Matrix4x4
{
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
} Matrix4x4;

inline Matrix4x4 Matrix4x4_CreateOrthographicOffCenter(
    const float left,
    const float right,
    const float bottom,
    const float top,
    const float zNearPlane,
    const float zFarPlane)
{
    return (Matrix4x4){
        2.0f / (right - left), 0, 0, 0,
        0, 2.0f / (top - bottom), 0, 0,
        0, 0, 1.0f / (zNearPlane - zFarPlane), 0,
        (left + right) / (left - right), (top + bottom) / (bottom - top), zNearPlane / (zNearPlane - zFarPlane), 1
    };
}

#endif //ATLAS_MATH_H
