#include "pch.h"
#include "main.h"
#include "GCSR.h"
#include <random>

#include "GameManager.h"

int main()
{
    GameManager* game = GameManager::GetInstance();

    while (game->getSceneManager()->getWindow()->IsOpen() && game->IsRunning()) {
        game->Run();
    }

    return 0;
}