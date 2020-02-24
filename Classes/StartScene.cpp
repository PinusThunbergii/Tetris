#include "StartScene.h"

using namespace cocos2d;

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto label = Label::createWithTTF("Tetris", "fonts/Marker Felt.ttf", 60);
    label->setAnchorPoint(Vec2(0,0));
    float offset = 10.0f;
    Vec2 pos =Vec2(visibleSize.width / 2.0f - label->getContentSize().width/2, 
                        visibleSize.height - label->getContentSize().height/2 - offset);
    label->setPosition(pos);
    this->addChild(label, 1);

    return true;
}

Scene *StartScene::createScene()
{
    return StartScene::create();
}
