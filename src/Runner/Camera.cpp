#include "pch.h"
#include "Camera.h"
#include "lib/Geometries/Geometry.h"
#include "Character.h"

Camera::Camera(sr::CameraType type) : sr::Camera(type)
{
}

void Camera::LookAt(sr::Geometry* target)
{
    gce::Vector3f32 toCenter = target->GetPosition() - GetPosition();
    float yaw = std::atan2(toCenter.x, toCenter.z) * (180.0f / gce::PI);
    float distanceXZ = std::sqrt(toCenter.x * toCenter.x + toCenter.z * toCenter.z);
    float pitch = -std::atan2(toCenter.y, distanceXZ) * (180.0f / gce::PI);

    SetRotation({ pitch, yaw, 0.0f });
}

void Camera::FollowPlayer(Character* player, float deltaTime)
{
    float speed = player->GetSpeed();

    gce::Vector3f32 camPos = GetPosition();
    camPos.z += player->GetSpeed() * deltaTime;
    SetPosition(camPos);
}