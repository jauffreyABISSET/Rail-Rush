#include "pch.h"
#include "GameManager.h"
#include "SceneManager.h"

#include "MainScene.h"
#include "DefeatScene.h"
#include "PauseScene.h"
#include "MenuScene.h"
#include "MenuScene2.h"

GameManager* GameManager::mInstance = nullptr;

GameManager* GameManager::GetInstance() {

    if (mInstance == nullptr) {
        mInstance = new GameManager();
    }

    return mInstance;
}

GameManager::GameManager()
{
    mSceneManager = new SceneManager();

    mSceneManager->AddScene("MainScene", new MainScene());
    mSceneManager->AddScene("MenuScene2", new MenuScene2());
    mSceneManager->AddScene("MenuScene", new MenuScene());
    mSceneManager->AddScene("DefeatScene", new DefeatScene());

    mSceneManager->SetScene("MenuScene");
}

void GameManager::Run()
{
    mSceneManager->Update();
    mSceneManager->Render();
}