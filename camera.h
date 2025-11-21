//
// Created by hoy on 11/19/25.
//

#ifndef ATLAS_CAMERA_H
#define ATLAS_CAMERA_H

typedef struct Matrix4x4 {
    float m11, m12, m13, m14;
    float m21, m22, m23, m24;
    float m31, m32, m33, m34;
    float m41, m42, m43, m44;
} Matrix4x4;

Matrix4x4 Matrix4x4_CreateOrthographicOffCenter(
    float left,
    float right,
    float bottom,
    float top,
    float zNearPlane,
    float zFarPlane) {
    return (Matrix4x4){
        2.0f / (right - left), 0, 0, 0,
        0, 2.0f / (top - bottom), 0, 0,
        0, 0, 1.0f / (zNearPlane - zFarPlane), 0,
        (left + right) / (left - right), (top + bottom) / (bottom - top), zNearPlane / (zNearPlane - zFarPlane), 1
    };
}

class Camera {
private:
    Matrix4x4 cameraMatrix = Matrix4x4_CreateOrthographicOffCenter(
        0,
        800,
        600,
        0,
        0,
        -1);
};


#endif //ATLAS_CAMERA_H
