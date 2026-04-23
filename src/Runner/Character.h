#pragma once
#include "lib/Geometries/Geometries.h"
#include "lib/Geometries/Geometry.h"
#include "lib/Texture.h"

class Character : public sr::Custom
{
	sr::Texture* mTexture;

	float mSpeed;
	float mMaxSpeed;
	float mCubeSize;

	float mVerticalVelocity = 0.0f;
	bool mIsJumping = false;
	const float mJumpForce = 9.0f;
	const float mGravity = -24.0f;

public:
	Character(String filepath, float speed, float cubeSize, sr::Texture* texture);

	void SetSpeed(float speed);
	void SetJumping(bool jumping) { mIsJumping = jumping; }
	void SetVerticalVelocity(float verticalVelocity) { mVerticalVelocity = verticalVelocity; }

	float GetSpeed() { return mSpeed; }
	float GetMaxSpeed() { return mMaxSpeed; }
	bool IsJumping() { return mIsJumping; }
	float GetVerticalVelocity() { return mVerticalVelocity; }
	float GetJumpForce() { return mJumpForce; }

	void MoveForward(float deltaTime);
	void Jump(float deltaTime, float groundY, bool spacePressed);
	void MoveSideways(float deltaTime, float spacingZ, bool rightPressed, bool leftPressed);

	void MoveUpDown(float deltaTime, float spacingZ, bool upPressed, bool downPressed, bool spacePressed);

	void MoveRightLeft(float deltaTime, float spacingY, bool rightPressed, bool leftPressed, bool spacePressed);

	int mGridPosX;
	int mGridPosY;
};