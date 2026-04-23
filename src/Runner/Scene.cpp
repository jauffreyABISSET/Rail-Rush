#include "pch.h"
#include "Scene.h"
#include "lib/Window.h"
#include "Camera.h"

void Scene::Init(sr::Window* _window, Camera* camera)
{
	mWindow = _window;
	mCamera = camera;
}