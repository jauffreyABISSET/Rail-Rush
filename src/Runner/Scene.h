#pragma once
#include "pch.h"
#include "lib/Window.h"
#include "lib/Texture.h"
#include "Camera.h"

struct AllTexture
{
    sr::Texture* textureRails = new sr::Texture("res/Obj/rail56.png");
    sr::Texture* textureTnt = new sr::Texture("res/Textures/TNT2.png");
    sr::Texture* textureBat = new sr::Texture("res/Obj/minecraft_-_bat.png");
    sr::Texture* textureTunnel = new sr::Texture("res/Obj/tunnel.png");
    sr::Texture* textureFloor = new sr::Texture("res/Textures/wood.png");
    sr::Texture* texturePlayer = new sr::Texture("res/Obj/W.png");
    sr::Texture* texturePortal = new sr::Texture("res/Obj/Nether.png");
    sr::Texture* textureTorche = new sr::Texture("res/Obj/torche.png");
    sr::Texture* texturePlay = new sr::Texture("res/Textures/Play.png");
    sr::Texture* textureExit = new sr::Texture("res/Textures/Exit.png");
};

class Scene
{
protected:
    sr::Window* mWindow;
    Camera* mCamera;

    AllTexture mAllTexture;

public:
    virtual ~Scene() = default;
    virtual void Init(sr::Window* _window, Camera* camera);
    virtual void Update() = 0;
    virtual void Render() = 0;
    virtual void Clear() = 0;
};