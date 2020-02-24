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
    auto button = ui::Button::create();
    button->setTitleText("Click");
    button->setPosition(Vec2(100, 100));
    //http://www.pixnbgames.com/blog/c/how-to-add-event-listener-to-button-cocos2d-x-3-and-cpp/
    //button->addClickEventListener(CC_CALLBACK_1(StartScene::onClick, this));
    button->addTouchEventListener(CC_CALLBACK_2(StartScene::onClick, this) );

    this->addChild(button);
    return true;
}

Scene *StartScene::createScene()
{
    return StartScene::create();
}

void StartScene::onClick(Ref* pSender, Widget::TouchEventType type)
{
    CCLOG("CLICK");
}