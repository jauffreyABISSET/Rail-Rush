#pragma once
#include "Scene.h"
#include "lib/Window.h"
#include "lib/Geometries/Geometries.h"
#include "lib/Texture.h"

#include "lib/Light.h"
#include "Camera.h"
#include "Character.h"

class MenuScene2 : public Scene
{
    std::vector<sr::Cube*> mTnt;
    std::vector<sr::Custom*> mBats;

    std::vector<sr::Custom*> mRails;

    std::vector<sr::Custom*> mEntities;

    std::vector<std::vector<int>> mCurrentLevel;
    std::vector<std::vector<int>> mNextLevel;

    float mCurrentLevelStartZ = 0.0f;
    float mNextLevelStartZ = 0.f;
    bool mHasStarted = false;
    bool mAddALine = false;

    float mNextSpawnMoment;

    int mIndice = 0;

    float mCubeSize = 1.0f;
    float mSpacingX = 1.f;
    float mSpacingZ = 0.6f;
    float mPlayerAngle = 0.0f;

    Character* mPlayer;

    float mVerticalVelocity = 0.0f;
    bool mIsJumping = false;
    const float mGravity = -8.0f;
    const float mJumpForce = 5.0f;
    bool mIsCameraInit = false;
    sr::Light* mPlayerLight;
    sr::Light* mCaveLight;

    sr::Custom* mPortal;
    sr::Custom* mCave;

    sr::Plane* mFloor;

public:
    void Init(sr::Window* _window, Camera* camera) override;
    void Update() override;
    void Render() override;
    void Clear() override;

    void CreateLevel(std::vector<std::vector<int>> level, float cubeSize, float spacingX, float spacingZ, float zOffSet);
};