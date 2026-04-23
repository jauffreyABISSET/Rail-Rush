#include "pch.h"
#include "MainScene.h"
#include "lib/Text.h"
#include "lib/Light.h"
#include "lib/Texture.h"
#include "lib/Window.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include "Character.h"
#include "GameManager.h"
#include "MenuScene.h"

std::vector<std::vector<int>> GetInfosFromTxt(const std::string& filePath) 
{
    std::vector<std::vector<int>> levelData;
    std::ifstream file(filePath);

    if (!file.is_open()) 
    {
        std::cerr << "Error : Unable to open : " << filePath << std::endl;
        return levelData;
    }

    std::string line;
    while (std::getline(file, line)) 
    {
        std::vector<int> row;
        for (char c : line) 
        {
            if (c == '0' || c == '1' || c == '2' || c == '3')
                row.push_back(c - '0');
        }
        if (!row.empty())
            levelData.push_back(row);
    }

    file.close();
    return levelData;
}

void MainScene::Init(sr::Window* _window, Camera* camera)
{
    Scene::Init(_window, camera);

    mCurrentLevel = GetInfosFromTxt("../../res/Levels/Level1.txt");
    mNextLevel = GetInfosFromTxt("../../res/Levels/Level2.txt");

    CreateLevel(mCurrentLevel, mCubeSize, mSpacingX, mSpacingZ, mNextLevelStartZ);

    mHasStarted = true;
    mCurrentLevelStartWorldZ = mRails.front()->GetPosition().z;
    mNextLevelStartZ = mCurrentLevel.size() * (1.0f + 0.6f);
    mNextSpawnMoment = mNextLevel.size() * (1.0f + 0.6f) * 0.25f;

    mPlayer = new Character("res/Obj/W.obj", 10.f, mCubeSize, mAllTexture.texturePlayer);
    mPlayer->SetPosition({
        mRails[0]->GetPosition().x + mCubeSize + mSpacingX,
        mRails[0]->GetPosition().y + 0.1f,
        mRails[0]->GetPosition().z - 3.f
        });
    mPlayer->SetRotation({ 0.0f, 0.0f, 0.0f });

    mController = new Controller(mPlayer);

    mCave = new sr::Custom("res/Obj/tunnel.obj");
    float tunnelLength = mCurrentLevel.size() * (mCubeSize + mSpacingZ);
    mCave->SetPosition({ 0.0f, 2.0f, tunnelLength * 0.5f });
    mCave->SetScale({ 1.0f, 1.0f, tunnelLength * 0.1f });
    mCave->SetTexture(*mAllTexture.textureTunnel);

    mFloor = new sr::Plane();
    float floorLength = mCurrentLevel.size() * (mCubeSize + mSpacingZ);
    mFloor->SetPosition({ 0.0f, -0.5f, mPlayer->GetPosition().z });
    mFloor->SetScale({ 7.5f, 1.0f, floorLength + 200.f });
    mFloor->SetTexture(*mAllTexture.textureFloor);

    mPlayerLight = new sr::Light(sr::Light::CreatePointLight(
        { mPlayer->GetPosition().x, mPlayer->GetPosition().y + 0.5f, mPlayer->GetPosition().z + 2.0f },
        { 1.0f, 0.7f, 0.6f, 1.0f }, 60.0f, 0.5f, 1.8f
    ));
    sr::Light::AddLight(*mPlayerLight);

    mCaveLight = new sr::Light(sr::Light::CreatePointLight(
        { mPlayer->GetPosition().x, mPlayer->GetPosition().y + 3.f, mPlayer->GetPosition().z },
        { 0.95f, 0.95f, 1.0f, 1.0f }, 80.0f, 0.8f, 0.5f
    ));
    sr::Light::AddLight(*mCaveLight);
}

void MainScene::Update() 
{
    if (mIsCameraInit == false)
    {
        float cameraDistance = 3.0f;
        float cameraHeight = -12.5f;
        gce::Vector3f32 playerPos = mPlayer->GetPosition();
        float dirZ = std::sin(gce::PI / 2);
        float dirX = std::cos(gce::PI / 2);

        mCamera->SetPosition({
            playerPos.x - dirX * cameraDistance,
            playerPos.y + cameraHeight + 15.0f,
            playerPos.z - dirZ * cameraDistance });
        mCamera->SetFOV(gce::PI / 2.0f);
        mCamera->SetNearPlane(0.001f);
        mCamera->SetFarPlane(200.0f);

        mIsCameraInit = true;
    }

    float deltaTime = mWindow->GetDeltaTime();

    mPlayer->MoveForward(deltaTime);

    mController->HandleMovement(deltaTime, mSpacingZ, mRails[0]->GetPosition().y);

    mCamera->FollowPlayer(mPlayer, deltaTime);
    mCamera->LookAt(mPlayer);

    sr::Light::RemoveLight(*mCaveLight);
    sr::Light::RemoveLight(*mPlayerLight);

    gce::Vector3f32 lightOffset2 = { 0.0f, 3.0f, 0.0f };
    gce::Vector3f32 lightOffset = { 0.0f, 0.75f, 3.0f };
    gce::Vector3f32 playerPos = mPlayer->GetPosition();

    mCaveLight->SetPosition(playerPos + lightOffset2);
    mPlayerLight->SetPosition(playerPos + lightOffset);

    sr::Light::AddLight(*mCaveLight);
    sr::Light::AddLight(*mPlayerLight);

    float playerZ = mPlayer->GetPosition().z;
    float unitZ = mCubeSize + mSpacingZ;
    float currentLevelWorldLen = (float)mCurrentLevel.size() * unitZ;
    float currentLevelEndZ = mCurrentLevelStartZ + currentLevelWorldLen;

    if (mAddALine && mIndice < mNextLevel.size()) 
    {
        CreateLevel(mNextLevel, mCubeSize, mSpacingX, mSpacingZ, mNextLevelStartZ);
        mIndice++;
        mAddALine = false;
    }

    if (playerZ > mNextSpawnMoment) 
    {
        CreateOrResizeTunnel(mNextSpawnMoment, mCurrentLevel.size());
        CreateOrResizeFloor(mNextSpawnMoment, mCurrentLevel.size());
        mNextSpawnMoment += mNextLevel.size() * 1.25f * 0.25f;
    }

    if (playerZ > currentLevelEndZ) 
    {
        mCurrentLevelStartZ = mNextLevelStartZ;
        mIndice = 0;
        float nextWorldLen = (float)mNextLevel.size() * (mCubeSize + mSpacingZ);
        mNextLevelStartZ = mCurrentLevelStartZ + nextWorldLen;
    }

    float relativeZ = mPlayer->GetPosition().z - mCurrentLevelStartWorldZ;
    mPlayer->mGridPosY = (int)(relativeZ / (mCubeSize + mSpacingZ));

    if (mPlayer->mGridPosY >= mCurrentLevel.size()) 
    {
        if (mIsLevelOne == false) {
            mCurrentLevel = mNextLevel;
            mNextLevel = GetInfosFromTxt("../../res/Levels/Level3.txt");
        }

        mPlayer->mGridPosY = 0;
        mCurrentLevelStartWorldZ = mPlayer->GetPosition().z - mSpacingZ * mCoeffCollision;
        mCoeffCollision += 0.005f;
        mIsLevelOne = false;
    }

    if (mPlayer->mGridPosY >= 0 && mPlayer->mGridPosY < mCurrentLevel.size()) 
    {
        float speed = mPlayer->GetMaxSpeed();

        int cell = mCurrentLevel[mPlayer->mGridPosY][mPlayer->mGridPosX];
        if (cell == 2 && (mPlayer->GetPosition().y <= mTnt[0]->GetPosition().y + mCubeSize))
        {
            GameManager::GetInstance()->getSceneManager()->SetScene("DefeatScene");
            std::cout << mCellsTraversed << std::endl;
        }
        else if (cell == 3) 
        {
            GameManager::GetInstance()->getSceneManager()->SetScene("DefeatScene");
        }

        mPlayer->SetSpeed(speed);
    }

    if (mPlayer->mGridPosY > mCellsTraversed)
    {
        mCellsTraversed = mPlayer->mGridPosY;
        GameManager::GetInstance()->SetCellsTraversed(mCellsTraversed);
    }

    EraseBehind();
}

void MainScene::Render() 
{
    mWindow->Begin(*mCamera);

    if (mCave) mWindow->Draw(*mCave);
    if (mFloor) mWindow->Draw(*mFloor);
    mWindow->Draw(*mPlayer);

    for (sr::Custom* rail : mRails) mWindow->Draw(*rail);
    for (sr::Cube* tnt : mTnt) mWindow->Draw(*tnt);
    for (sr::Custom* bat : mBats) mWindow->Draw(*bat);

    mWindow->End();
    mWindow->Display();
}

void MainScene::EraseBehind() 
{
    float playerZ = mPlayer->GetPosition().z;

    for (int i = (int)mTnt.size() - 1; i >= 0; --i) 
    {
        if (mTnt[i]->GetPosition().z < playerZ - 5.0f) 
        {
            mTnt.erase(mTnt.begin() + i);
            mAddALine = true;
        }
    }

    for (int i = (int)mBats.size() - 1; i >= 0; --i) 
    {
        if (mBats[i]->GetPosition().z < playerZ - 5.0f) 
        {
            mBats.erase(mBats.begin() + i);
            mAddALine = true;
        }
    }

    for (int i = (int)mRails.size() - 1; i >= 0; --i) 
    {
        if (mRails[i]->GetPosition().z < playerZ - 5.0f) 
        {
            mRails.erase(mRails.begin() + i);
            mAddALine = true;
        }
    }
}

void MainScene::Clear()
{
    mRails.clear();
    mTnt.clear();
    mBats.clear();

    sr::Light::RemoveLight(*mPlayerLight);
    sr::Light::RemoveLight(*mCaveLight);
}

void MainScene::CreateLevel(std::vector<std::vector<int>> level, float cubeSize, float spacingX, float spacingZ, float zOffSet) {
    float gridSizeX = level[0].size();
    float gridSizeZ = level.size();
    int min = 0;
    int max = gridSizeZ;

    if (mHasStarted) 
    {
        min = mIndice;
        max = min + 1;
    }
    float totalSizeX = gridSizeX * (cubeSize + spacingX) - spacingX;
    float totalSizeZ = gridSizeZ * (cubeSize + spacingZ) - spacingZ;

    for (int x = 0; x < gridSizeX; ++x) 
    {
        for (int z = min; z < max; ++z) 
        {
            int cell = level[z][x];
            if (cell == 0) continue;

            float xPos = x * (cubeSize + spacingX) - totalSizeX / 2.0f + cubeSize / 2.0f;
            float zPos = zOffSet + z * (cubeSize + spacingZ) - totalSizeZ / 2.0f + cubeSize / 2.0f;
            float yPos = 0.0f;

            if (cell == 1) 
            {
                sr::Custom* rail = new sr::Custom("res/Obj/rail69.obj");
                rail->SetPosition({ xPos, yPos + cubeSize, zPos });
                rail->SetScale({ cubeSize, cubeSize, cubeSize });
                rail->SetTexture(*mAllTexture.textureRails);
                rail->SetRotation({ 0.0f, 0.0f, 0.0f });
                mRails.push_back(rail);
            }
            else if (cell == 2) 
            {
                sr::Cube* tnt = new sr::Cube();
                tnt->SetPosition({ xPos, yPos + cubeSize, zPos });
                tnt->SetTexture(*mAllTexture.textureTnt);
                tnt->SetScale({ cubeSize, cubeSize, cubeSize });
                tnt->SetRotation({ 0.0f, 0.0f, 180.0f });
                mTnt.push_back(tnt);
            }
            else if (cell == 3) 
            {
                sr::Custom* bat = new sr::Custom("res/Obj/minecraft_-_bat.obj");
                bat->SetPosition({ xPos, yPos + cubeSize * 2.f, zPos });
                bat->SetScale({ 0.04f, 0.04f, 0.04f });
                bat->SetTexture(*mAllTexture.textureBat);
                bat->SetRotation({ 0.0f, 180.0f, 0.0f });
                mBats.push_back(bat);
            }
        }
    }
}

void MainScene::CreateOrResizeTunnel(float startZ, float levelLength) 
{
    float tunnelLength = levelLength * (mCubeSize + mSpacingZ) - 2.f;
    if (!mCave) 
    {
        mCave = new sr::Custom("res/Obj/tunnel.obj");
        mCave->SetTexture(*mAllTexture.textureTunnel);
    }
    mCave->SetPosition({ 0.0f, 2.0f, startZ + tunnelLength * 0.5f });
    mCave->SetScale({ 1.0f, 1.0f, tunnelLength / 10.0f });
}

void MainScene::CreateOrResizeFloor(float startZ, float levelLength) 
{
    float floorLength = levelLength * (mCubeSize + mSpacingZ) - 2.f;
    if (!mFloor) 
    {
        mFloor = new sr::Plane();
        mFloor->SetTexture(*mAllTexture.textureFloor);
    }
    mFloor->SetPosition({ 0.0f, -0.5f, startZ + floorLength * 0.5f });
    mFloor->SetScale({ 7.5f, 1.0f, floorLength + 20.f });
}
