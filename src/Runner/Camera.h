#pragma once
#include "lib/Camera.h"
#include "Character.h"

class Camera : public sr::Camera
{
public:
	Camera(sr::CameraType type);

	void LookAt(sr::Geometry* target);

	void FollowPlayer(Character* player, float deltaTime);
};