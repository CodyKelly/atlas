#ifndef ATLAS_CAMERASYSTEM_H
#define ATLAS_CAMERASYSTEM_H

#include "math.h"
#include "Transform.h"

struct CameraConfig
{
    float zoomMin = 0.1f;
    float zoomMax = 10.0f;
    float zoomSpeed = 0.1f;
    float moveSpeed = 500.0f;
    float smoothing = 5.0f; // For lerp-based smoothing
};

struct CameraState
{
    Transform current;
    Transform target;
    Vector2 velocity;
    Vector2 viewportSize;
    bool isDirty = true;
};

struct CameraMatrices
{
    Matrix4x4 view;
    Matrix4x4 projection;
    Matrix4x4 viewProjection;
};

class Camera
{
private:
    CameraState _state;
    CameraMatrices _matrices;
    bool _matricesDirty = true;

public:
    Camera() = default;
    explicit Camera(Vector2 viewportSize);

    const CameraState& GetState() const { return _state; }
    CameraState& GetState() { return _state; }

    const Matrix4x4& GetViewProjectionMatrix();

    void SetViewportSize(Vector2 size);
    void SetPosition(Vector2 position);
    void SetTargetPosition(Vector2 position);
    void SetScale(Vector2 scale);
    void SetTargetScale(Vector2 scale);

    Vector2 GetPosition() const { return _state.current.position; }
    Vector2 GetScale() const { return _state.current.scale; }
    Vector2 GetViewportSize() const { return _state.viewportSize; }

    Vector2 ScreenToWorld(Vector2 screenPos) const;
    Vector2 WorldToScreen(Vector2 worldPos) const;

    void MarkDirty() { _matricesDirty = true; }
};

class CameraController
{
private:
    Camera* _camera;
    CameraConfig _config;

public:
    CameraController() : _camera(nullptr)
    {
    }

    CameraController(Camera* camera, CameraConfig config = {});

    void SetCamera(Camera* camera) { _camera = camera; }
    void SetConfig(const CameraConfig& config) { _config = config; }
    const CameraConfig& GetConfig() const { return _config; }

    void Pan(Vector2 delta);
    void Zoom(float delta);
    void ZoomToPoint(float delta, Vector2 screenPoint);

    void Update(float deltaTime);

    void SnapToTarget();

    void Follow(Vector2 worldPosition, float deltaTime);
};

#endif //ATLAS_CAMERASYSTEM_H
