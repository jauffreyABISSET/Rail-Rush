#include "pch.h"
#include "Controller.h"
#include "lib/Inputs/InputsMethods.h"

void Controller::HandleMovement(float deltaTime, float spacingZ, float groundY)
{
    bool rightPressed = false;
    bool leftPressed = false;
    bool spacePressed = false;

    if (sr::GetKey(sr::Keyboard::Q) || sr::GetKey(sr::Keyboard::LEFT_ARROW))
    {
        leftPressed = true;
    }
    else if (sr::GetKey(sr::Keyboard::D) || sr::GetKey(sr::Keyboard::RIGHT_ARROW))
    {
        rightPressed = true;
    }

    if (sr::GetKey(sr::Keyboard::SPACE))
    {
        spacePressed = true;
    }

    mPlayer->Jump(deltaTime, groundY, spacePressed);
    mPlayer->MoveSideways(deltaTime, spacingZ, rightPressed, leftPressed);
}

void Controller::MenuMovement(float deltaTime, float spacingZ, float groundY)
{
    bool UpPressed = false;
    bool DownPressed = false;
    bool SpacePressed = false;

    if (sr::GetKey(sr::Keyboard::Z) || sr::GetKey(sr::Keyboard::UP_ARROW))
    {
        UpPressed = true;
    }
    else if (sr::GetKey(sr::Keyboard::S) || sr::GetKey(sr::Keyboard::DOWN_ARROW))
    {
        DownPressed = true;
    }
    if (sr::GetKey(sr::Keyboard::SPACE) || sr::GetKey(sr::Keyboard::SPACE))
    {
        SpacePressed = true;
    }
    mPlayer->MoveUpDown(deltaTime, spacingZ, UpPressed, DownPressed, SpacePressed);
}

void Controller::DefeatMovement(float deltaTime, float spacingZ, float groundY)
{
    bool RightPressed = false;
    bool LeftPressed = false;
    bool SpacePressed = false;

    if (sr::GetKey(sr::Keyboard::D) || sr::GetKey(sr::Keyboard::RIGHT_ARROW))
    {
        RightPressed = true;
    }
    else if (sr::GetKey(sr::Keyboard::Q) || sr::GetKey(sr::Keyboard::LEFT_ARROW))
    {
        LeftPressed = true;
    }
    if (sr::GetKey(sr::Keyboard::SPACE) || sr::GetKey(sr::Keyboard::SPACE))
    {
        SpacePressed = true;
    }
    mPlayer->MoveRightLeft(deltaTime, spacingZ, RightPressed, LeftPressed, SpacePressed);
}
