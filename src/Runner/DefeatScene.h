#pragma once
#include "Scene.h"
#include "lib/Window.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Texture.h"
#include "lib/Text.h"
#include "lib/Light.h"
#include "Camera.h"
#include "Character.h"
#include "Controller.h"
#include <vector> 

class DefeatScene : public Scene
{
	Controller* mController;
	sr::Custom* mBats;
	sr::Custom* mCave;
	sr::Plane* mFloor;
	Character* mPlayer;
	sr::Light* mPlayerLight;
	sr::Light* mPlayerLight2;
	sr::Cube* mTNT;
	sr::Custom* mPortal;
	sr::Custom* mRail;
	sr::Text* mScoreText = nullptr;

	bool mIsCameraInit = false;

	float mSpacingZ = 0.6f;
	float mWindowSize = 1080.0f;
	float mBatRotationY = 0.0f;
	float mPlayerRotationY = 0.0f;
	float mTNTRotationY = 0.0f;
	float mRailRotationY = 0.0f;

public:
	void Init(sr::Window* _window, Camera* camera) override;
	void Update() override;
	void Render() override;
	void Clear() override;
};

