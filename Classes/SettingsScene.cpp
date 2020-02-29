#include "SettingsScene.h"

bool SettingsScene::init()
{
    if(!Scene::init())
    {
        return false;
    }

    

    return true;
}

Scene* SettingsScene::createScene()
{
    return Scene::create();
}