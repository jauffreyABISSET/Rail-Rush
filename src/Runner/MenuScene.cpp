#include "pch.h"
#include "MenuScene.h"
#include "MenuScene2.h"
#include "lib/Inputs/InputsMethods.h"
#include "GameManager.h"
#include "Controller.h"

void MenuScene::Init(sr::Window* _window, Camera* camera)
{
    Scene::Init(_window, camera);

    mPlayer = new Character("res/Obj/W.obj", 10.f, 1.0f, mAllTexture.texturePlayer);
    mPlayer->SetPosition({ 2.5f, 3.0f, -2.0f });
    mPlayer->SetRotation({ 0.0f, 0.0f, 0.0f });

    mController = new Controller(mPlayer);

    float cameraDistance = 5.0f;
    float cameraHeight = -15.5f;

    gce::Vector3f32 playerPos = mPlayer->GetPosition();
    float dirZ = std::sin(mPlayerAngle + gce::PI / 2);
    float dirX = std::cos(mPlayerAngle + gce::PI / 2);

    mPlay = new sr::Plane();
    mPlay->SetPosition({0.f, 3.5f, -1.f});
    mPlay->SetScale({ 3.f, 1.f, 1.5f });
    mPlay->SetColor({ 0.f, 1.f, 0.f });
    mPlay->SetTexture(*mAllTexture.texturePlay);
    mPlay->SetRotation({-90.0f, 0.0f, 0.f});

    mExit = new sr::Plane();
    mExit->SetPosition({ 0.f, 0.5f, -1.f });
    mExit->SetScale({ 3.f, 1.f, 1.5f });
    mExit->SetColor({ 1.f, 0.f, 0.f });
    mExit->SetTexture(*mAllTexture.textureExit);
    mExit->SetRotation({ -90.0f, 0.0f, 0.f });

    mPortal = new sr::Custom("res/Obj/Nether.obj");
    mPortal->SetPosition({ 1.5f, -1.5f, mPlay->GetPosition().z - 8.f});
    mPortal->SetScale({ 1.f, 1.f, 1.f });

    mPortal->SetTexture(*mAllTexture.texturePortal);
    mCamera->SetPosition({dirX * cameraDistance,playerPos.y + cameraHeight + 15.0f, playerPos.z - dirZ * cameraDistance });
    mCamera->SetFOV(gce::PI / 2.0f);
    mCamera->SetNearPlane(0.001f);
    mCamera->SetFarPlane(200.0f);

    mCave = new sr::Custom("res/Obj/tunnel.obj");
    mCave->SetPosition({ 0.0f, 2.0f,0.0f });
    mCave->SetScale({ 1.0f, 1.0f, 20.f });
    mCave->SetTexture(*mAllTexture.textureTunnel);

    mFloor = new sr::Plane();
    mFloor->SetPosition({ 0.0f, -0.5f, mPlayer->GetPosition().z });
    mFloor->SetScale({ 7.5f, 1.0f, 400.f });
    mFloor->SetTexture(*mAllTexture.textureFloor);

    mBats = new sr::Custom("res/Obj/minecraft_-_bat.obj");
    mBats->SetPosition({ -2.9f, 3.3f, -1.f });
    mBats->SetScale({ 0.04f, 0.04f, 0.04f });
    mBats->SetTexture(*mAllTexture.textureBat);
    mBats->SetRotation({ 180.0f, 0.0f, 0.0f });

    mTNT = new sr::Cube();
    mTNT->SetPosition({ -2.9f, 0.5f, -0.5f });
    mTNT->SetScale({ 1.f, 1.f, 1.f});
    mTNT->SetTexture(*mAllTexture.textureTnt);
    mTNT->SetRotation({ 0.0f, 180.0f, 0.0f });

    mPlayerLight = new sr::Light(sr::Light::CreatePointLight({ mTNT->GetPosition().x, mTNT->GetPosition().y - 0.5f, mTNT->GetPosition().z - 0.8f }, { 1.0f, 0.7f, 0.6f, 1.0f }, 38.0f, 0.5f, 1.2f));
    sr::Light::AddLight(*mPlayerLight);

    mPlayerLight2 = new sr::Light(sr::Light::CreatePointLight({ mPlayer->GetPosition().x, mPlayer->GetPosition().y - 0.5f, mPlayer->GetPosition().z - 0.1f }, { 1.0f, 0.7f, 0.6f, 1.0f }, 40.0f, 0.5f, 1.3f));
    sr::Light::AddLight(*mPlayerLight2);
}

void MenuScene::Update()
{
    float deltaTime = mWindow->GetDeltaTime();

    mController->MenuMovement(deltaTime, mSpacingZ, mPlay->GetPosition().y);

    if (mBats)
    {
        mBatRotationY += 50.f * deltaTime;
        mBats->SetRotation({ 0.0f, mBatRotationY, 0.0f });
    }

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
}

void MenuScene::Render()
{
    mWindow->Begin(*mCamera);

    if (mCave)
        mWindow->Draw(*mCave);

    if (mPortal)
        mWindow->Draw(*mPortal);

    if(mPlay)
        mWindow->Draw(*mPlay);

    if (mExit)
        mWindow->Draw(*mExit);

    if (mFloor)
        mWindow->Draw(*mFloor);

    if (mTNT)
        mWindow->Draw(*mTNT);

    mWindow->Draw(*mPlayer);

    if (mBats)
        mWindow->Draw(*mBats);

    mWindow->End();
    mWindow->Display();
}

void MenuScene::Clear()
{
    sr::Light::RemoveLight(*mPlayerLight);
    sr::Light::RemoveLight(*mPlayerLight2);
}