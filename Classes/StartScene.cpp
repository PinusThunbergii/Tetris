#include "StartScene.h"

bool StartScene::init()
{
    if(!Scene::init()) return false;
    //auto label = Label::create
}

Scene* StartScene::createScene()
{
    return StartScene::create();
}