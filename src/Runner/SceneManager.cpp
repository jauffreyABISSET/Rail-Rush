#include "pch.h"
#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager()
{
    mCamera = new Camera(sr::CameraType::PERSPECTIVE);
    mCamera->SetFOV(gce::PI / 2.0f);
    mCamera->SetNearPlane(0.001f);
    mCamera->SetFarPlane(200.0f);
}

SceneManager::~SceneManager()
{
    for (auto& pair : mScenes)
        delete pair.second;
    mScenes.clear();
}

void SceneManager::AddScene(const std::string& name, Scene* scene)
{
    if (mScenes.contains(name))
    {
        return;
    }
    mScenes[name] = scene;
    scene->Init(&mWindow, mCamera);
}

void SceneManager::SetScene(const std::string& name)
{
    auto it = mScenes.find(name);
    if (it == mScenes.end())
    {
        return;
    }

    if (mCurrentScene)
    {
        mCurrentScene->Clear();
    }
    mCurrentScene = it->second;
}

void SceneManager::Update()
{
    if (mCurrentScene)
        mCurrentScene->Update();
}

void SceneManager::Render()
{
    if (mCurrentScene)
        mCurrentScene->Render();
}

