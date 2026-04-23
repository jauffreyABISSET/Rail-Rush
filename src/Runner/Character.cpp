#include "pch.h"
#include "Character.h"
#include "GameManager.h"

Character::Character(String filepath, float speed, float cubeSize, sr::Texture* texture) : sr::Custom(filepath)
{
	mTexture = texture;
	SetTexture(*mTexture);

	mGridPosX = 1;
	mGridPosY = 0;

    mCubeSize = cubeSize;
	mSpeed = speed;
    mMaxSpeed = mSpeed;
}

void Character::SetSpeed(float speed)
{
    mSpeed = speed;

    if (mSpeed > mMaxSpeed)
        mMaxSpeed = mSpeed;
}

void Character::MoveForward(float deltaTime)
{
	gce::Vector3f32 pos = GetPosition();
	pos.z += mSpeed * deltaTime;
	SetPosition(pos);
}

void Character::Jump(float deltaTime, float groundY, bool spacePressed)
{
    gce::Vector3f32 pos = GetPosition();

    if (spacePressed && !mIsJumping)
    {
        mIsJumping = true;
        mVerticalVelocity = mJumpForce;
    }

    mVerticalVelocity += mGravity * deltaTime;

    pos.y += mVerticalVelocity * deltaTime;

    if (pos.y <= groundY)
    {
        pos.y = groundY;
        mVerticalVelocity = 0.0f;
        mIsJumping = false;
    }

    SetPosition(pos);
}

void Character::MoveSideways(float deltaTime, float spacingZ, bool rightPressed, bool leftPressed)
{
    float speed = GetSpeed() * deltaTime;

    gce::Vector3f32 pos = GetPosition();

    static int currentIndex = 1;
    static int frameCounter = 2;
    static int framesPerMove = 7;

    frameCounter++;
    if (frameCounter >= framesPerMove)
    {
        if ((leftPressed) && currentIndex > 0)
        {
            currentIndex--;
            mGridPosX--;
        }
        else if ((rightPressed) && currentIndex < 2)
        {
            currentIndex++;
            mGridPosX++;
        }

        frameCounter = 0;
    }

    float stepX = mCubeSize + spacingZ;
    float targetX = (currentIndex - 1) * stepX;

    float lerpSpeed = 0.2f;
    pos.x += (targetX - pos.x) * lerpSpeed;

    SetPosition(pos);
}

void Character::MoveUpDown(float deltaTime, float spacingY, bool upPressed, bool downPressed, bool spacePressed)
{
    float speed = GetSpeed() * deltaTime;

    gce::Vector3f32 pos = GetPosition();

    static int currentIndex = 0;
    static int frameCounter = 0;
    static int framesPerMove = 7;

    frameCounter++;
    if (frameCounter >= framesPerMove)
    {
        if ((downPressed) && currentIndex > 0)
        {
            currentIndex--;
            SetColor({ 1.f, 0.f, 0.f });
        }
        else if ((upPressed) && currentIndex < 1)
        {
            currentIndex++;
            SetColor({ 0.f, 1.f, 0.f });
        }

        if ((spacePressed) && currentIndex == 1)
        {
            GameManager::GetInstance()->getSceneManager()->SetScene("MenuScene2");
        }
        else if ((spacePressed) && currentIndex == 0)
        {
            GameManager::GetInstance()->SetRunning(false);
        }

        frameCounter = 0;
    }

    float stepY = 3.f;
    float targetY = (currentIndex) * stepY;

    float lerpSpeed = 0.2f;
    pos.y += (targetY - pos.y) * lerpSpeed;

    SetPosition(pos);
}

void Character::MoveRightLeft(float deltaTime, float spacingY, bool rightPressed, bool leftPressed, bool spacePressed)
{
    float speed = GetSpeed() * deltaTime;

    gce::Vector3f32 pos = GetPosition();

    static int currentIndex = 0;
    static int frameCounter = 0;
    static int framesPerMove = 7;

    frameCounter++;
    if (frameCounter >= framesPerMove)
    {
        if ((leftPressed) && currentIndex > 0)
        {
            currentIndex--;
            SetColor({ 1.f, 0.f, 0.f });
        }
        else if ((rightPressed) && currentIndex < 1)
        {
            currentIndex++;
            SetColor({ 0.f, 1.f, 0.f });
        }

        if ((spacePressed) && currentIndex == 1)
        {
            GameManager::GetInstance()->getSceneManager()->SetScene("MenuScene");
        }
        else if ((spacePressed) && currentIndex == 0)
        {
            GameManager::GetInstance()->SetRunning(false);
        }

        frameCounter = 0;
    }

    float stepX = 2.8f;
    float targetX = (currentIndex - 0.3f)*stepX;

    float lerpSpeed = 0.2f;
    pos.x += (targetX - pos.x) * lerpSpeed;

    SetPosition(pos);
}