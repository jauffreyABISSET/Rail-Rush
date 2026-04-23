#pragma once
#include "SceneManager.h"
#include "lib/Text.h"

class GameManager
{
	static GameManager* mInstance;

	SceneManager* mSceneManager;

	bool mIsRunning = true;

	int mCellsTraversed = 0;

public:
	GameManager();

	static GameManager* GetInstance();

	SceneManager* getSceneManager() { return mSceneManager; }

	bool IsRunning() { return mIsRunning; }
	void SetRunning(bool running) { mIsRunning = running; }

	void SetCellsTraversed(int cells) { mCellsTraversed = cells; }
	int GetCellsTraversed() const { return mCellsTraversed; }

	void Run();
};