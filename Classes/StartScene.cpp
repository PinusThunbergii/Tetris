#include "StartScene.h"

using namespace cocos2d;

bool StartScene::init()
{
    if(!Scene::init()) 
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto label = Label::createWithTTF("Tetris", "fonts/Marker Felt.ttf", 24);
    label->setPosition(Vec2::ZERO);
    this->addChild(label, 1);

    return true;
}

Scene* StartScene::createScene()
{
    return StartScene::create();
}