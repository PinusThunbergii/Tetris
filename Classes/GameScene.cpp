#include "GameScene.h"
#include "StartScene.h"

bool GameScene::init()
{
    if(!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    backButton = Button::create("icons/back.png", "icons/back_selected.png");
    backButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    backButton->setScale(visibleSize.height / 3000);
    backButton->setPosition(Vec2::ZERO);
    backButton->addClickEventListener(CC_CALLBACK_0(onClick_backButton, this));
    this->addChild(backButton, -1);

    return true;
}

Scene* GameScene::createScene()
{
    return GameScene::create();
}

void GameScene::onClick_backButton(Ref *sender)
{
    Director::getInstance()->replaceScene(StartScene::create());
}