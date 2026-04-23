#include "pch.h"
#include "DefeatScene.h"
#include "lib/Inputs/InputsMethods.h"
#include "GameManager.h"
#include "Controller.h"
#include <string>

void DefeatScene::Init(sr::Window* _window, Camera* camera)
{
    Scene::Init(_window, camera);

    mPlayer = new Character("res/Obj/W.obj", 10.f, 1.0f, mAllTexture.texturePlayer);
    mPlayer->SetPosition({ 2.0f, 1.f, -2.0f });
    mPlayer->SetRotation({ 0.0f, 0.0f, 0.0f });

    mController = new Controller(mPlayer);

    mPortal = new sr::Custom("res/Obj/Nether.obj");
    mPortal->SetPosition({ 1.8f, -1.8f, mPlayer->GetPosition().z - 7.f });
    mPortal->SetScale({ 1.2f, 1.2f, 1.2f });
    mPortal->SetTexture(*mAllTexture.texturePortal);

    mCave = new sr::Custom("res/Obj/tunnel.obj");
    mCave->SetPosition({ 0.0f, 2.0f,0.0f });
    mCave->SetScale({ 1.0f, 1.0f, 20.f });
    mCave->SetTexture(*mAllTexture.textureTunnel);

    mFloor = new sr::Plane();
    mFloor->SetPosition({ 0.0f, -0.5f, mPlayer->GetPosition().z });
    mFloor->SetScale({ 7.5f, 1.0f, 400.f });
    mFloor->SetTexture(*mAllTexture.textureFloor);

    mBats = new sr::Custom("res/Obj/minecraft_-_bat.obj");
    mBats->SetPosition({ -2.5f, 0.2f, -2.5f });
    mBats->SetScale({ 0.04f, 0.04f, 0.04f });
    mBats->SetTexture(*mAllTexture.textureBat);
    mBats->SetRotation({ 0.f, 180.0f, 0.0f });

    mRail = new sr::Custom("res/Obj/rail69.obj");
    mRail->SetPosition({ 2.0f, 0.2f, -2.0f });
    mRail->SetScale({ 1.f, 1.f, 1.f });
    mRail->SetTexture(*mAllTexture.textureRails);

    mTNT = new sr::Cube();
    mTNT->SetPosition({ -1.f, 0.1f, -1.f });
    mTNT->SetScale({ 1.f, 1.f, 1.f });
    mTNT->SetTexture(*mAllTexture.textureTnt);
    mTNT->SetRotation({ 0.0f, 180.0f, 0.0f });

    mScoreText = new sr::Text(L"TextScore");
    mScoreText->SetColor(gce::Color(127.f, 0.f, 255.f, 255.f));
    mScoreText->SetPosition({ 830.f, 400.f });
}

void DefeatScene::Update()
{
    if (mIsCameraInit == false)
    {
        float cameraDistance = 5.0f;
        float cameraHeight = -14.f;

        gce::Vector3f32 playerPos = mPlayer->GetPosition();
        float dirZ = std::sin(gce::PI / 2);
        float dirX = std::cos(gce::PI / 2);

        mCamera->SetPosition({ dirX * cameraDistance,playerPos.y + cameraHeight + 15.0f, playerPos.z - dirZ * cameraDistance });
        mCamera->SetRotation({ 0.0f, 0.0f, 0.0f });
        mCamera->SetFOV(gce::PI / 2.0f);
        mCamera->SetNearPlane(0.001f);
        mCamera->SetFarPlane(200.0f);

        mIsCameraInit = true;
    }

    mPlayerLight = new sr::Light(sr::Light::CreatePointLight({ mTNT->GetPosition().x, mTNT->GetPosition().y + 1.5f, mTNT->GetPosition().z }, { 1.0f, 0.7f, 0.6f, 1.0f }, 25.0f, 0.4f, 0.2f));
    sr::Light::AddLight(*mPlayerLight);

    mPlayerLight2 = new sr::Light(sr::Light::CreatePointLight({ mPlayer->GetPosition().x, mPlayer->GetPosition().y + 1.5f, mPlayer->GetPosition().z }, { 1.0f, 0.7f, 0.6f, 1.0f }, 25.0f, 0.4f, 0.2f));
    sr::Light::AddLight(*mPlayerLight2);

    float deltaTime = mWindow->GetDeltaTime();
    mController->DefeatMovement(deltaTime, mSpacingZ, mBats->GetPosition().x);

    if (mPlayer)
    {
        mPlayerRotationY += 20.f * deltaTime;
        mPlayer->SetRotation({ 0.0f, mPlayerRotationY, 0.0f });
    }

    if (mTNT)
    {
        mTNTRotationY += 50.f * deltaTime;
        mTNT->SetRotation({ 0.0f, mTNTRotationY, 0.0f });
    }

    if (mRail)
    {
        mRailRotationY += 50.f * deltaTime;
        mRail->SetRotation({ 0.0f, mRailRotationY, 0.0f });
    }

    int cells = GameManager::GetInstance()->GetCellsTraversed();
    mScoreText->SetText(std::wstring(L"Score : ") + std::to_wstring(cells));
}

void DefeatScene::Render()
{
    mWindow->Begin(*mCamera);

    if (mCave)
        mWindow->Draw(*mCave);

    if (mPortal)
        mWindow->Draw(*mPortal);

    if (mFloor)
        mWindow->Draw(*mFloor);

    if (mTNT)
        mWindow->Draw(*mTNT);

    if (mRail)
        mWindow->Draw(*mRail);

    mWindow->Draw(*mPlayer);

    if (mScoreText)
        mWindow->DrawText(*mScoreText);

    if (mBats)
        mWindow->Draw(*mBats);

    mWindow->End();
    mWindow->Display();
}

void DefeatScene::Clear()
{
    sr::Light::RemoveLight(*mPlayerLight);
    sr::Light::RemoveLight(*mPlayerLight2);
}
