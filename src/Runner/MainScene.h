#pragma once
#include "Scene.h"
#include "lib/Window.h"
#include "lib/Geometries/Geometries.h"

#include "lib/Light.h"
#include "Camera.h"
#include "Character.h"
#include "Controller.h"

class MainScene : public Scene
{
    Character* mPlayer;
    Controller* mController;
    
    std::vector<sr::Cube*> mTnt;
    std::vector<sr::Custom*> mBats;
    std::vector<sr::Custom*> mRails;

    std::vector<std::vector<int>> mCurrentLevel;
    std::vector<std::vector<int>> mNextLevel;

    int mCellsTraversed = 0; 
    float mCurrentLevelStartWorldZ = 0.0f;
    float mCurrentLevelStartZ = 0.0f;
    float mNextLevelStartZ = 0.f;
    bool mHasStarted = false;
    bool mAddALine = false;
    float mNextSpawnMoment;
    int mIndice = 0;
    float mCoeffCollision = -0.05f;

    bool mIsCameraInit = false;
    bool mIsLevelOne = true;

    float mCubeSize = 1.0f;
    float mSpacingX = 1.f;
    float mSpacingZ = 0.6f;
    float mCurrentPos = 0.f;

    sr::Light* mPlayerLight;
    sr::Light* mCaveLight;
    sr::Custom* mCave;
    sr::Plane* mFloor;

public:
    void Init(sr::Window* _window, Camera* camera) override;
    void Update() override;
    void Render() override;

    void EraseBehind();
    void Clear() override;

    void CreateLevel(std::vector<std::vector<int>> level, float cubeSize, float spacingX, float spacingZ, float zOffSet);
    void CreateOrResizeTunnel(float startZ, float levelLength);
    void CreateOrResizeFloor(float startZ, float levelLength);
};


//TODO : mettre dans dans scene.h
std::vector<std::vector<int>> GetInfosFromTxt(const std::string& filePath);