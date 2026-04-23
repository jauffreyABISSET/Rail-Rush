#pragma once
#include "lib/Window.h"
#include "lib/Text.h"

#include "Scene.h"
#include <unordered_map>
#include "Camera.h"

class SceneManager
{
    sr::Window mWindow{ L"Runner", 1920, 1080, sr::Window::FLAG_ENABLE_SHADOWPASS | sr::Window::FLAG_MSAA_X4 };

    std::unordered_map<std::string, Scene*> mScenes;
    Camera* mCamera;
    Scene* mCurrentScene = nullptr;

public:
    SceneManager();
    ~SceneManager();

    void AddScene(const std::string& name, Scene* scene);
    void SetScene(const std::string& name);
    Camera* GetCamera() { return mCamera; }
    void Update();
    void Render();
    sr::Window* getWindow() { return &mWindow; }
};