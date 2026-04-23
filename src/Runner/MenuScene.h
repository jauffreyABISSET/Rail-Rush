#pragma once
#include "Scene.h"
#include "lib/Window.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Texture.h"

#include "lib/Light.h"
#include "Camera.h"
#include "Character.h"
#include "Controller.h"

class MenuScene : public Scene
{
	std::vector<sr::Custom*> mRails;

	Controller* mController;
	sr::Custom* mBats;
	sr::Plane* mPlay;
	sr::Custom* mCave;
	sr::Plane* mFloor;
	Character* mPlayer;
	sr::Plane* mExit;
	sr::Light* mPlayerLight;
	sr::Light* mPlayerLight2;
	sr::Cube* mTNT;
	sr::Custom* mPortal;

	float mSpacingZ = 0.6f;
	float mPlayerAngle = 0.0f;
	float mWindowSize = 1080.0f;
	float mBatRotationY = 0.0f;
	float mPlayerRotationY = 0.0f;
	float mTNTRotationY = 0.0f;

public:
	void Init(sr::Window* _window, Camera* camera) override;
	void Update() override;
	void Render() override;
	void Clear() override;
};