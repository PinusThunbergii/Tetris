#include "StartScene.h"
#include "SettingsScene.h"
#include "GameScene.h"

bool StartScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    //"Tetris" label
    auto label = Label::createWithTTF("Tetris", "fonts/Marker Felt.ttf", visibleSize.height/6.0f);
    label->setTextColor(Color4B::RED);
    label->setAnchorPoint(Vec2(0, 0));
    float offset = 10.0f;
    Vec2 pos = Vec2(visibleSize.width / 2.0f - label->getContentSize().width / 2,
                    visibleSize.height - label->getContentSize().height );
    label->setPosition(pos);
    this->addChild(label, 1);

    //Menu
    
    Vector<MenuItem*> items;
    auto startGameMenuItem = MenuItemFont::create("Start");
    auto settingsMenuItem = MenuItemFont::create("Settings");
    settingsMenuItem->setCallback(CC_CALLBACK_0(onClick_goToSettings, this));
    startGameMenuItem->setCallback([&](Ref* sender){Director::getInstance()->replaceScene(GameScene::create());});
    items.pushBack(settingsMenuItem);
    items.pushBack(startGameMenuItem);
    

    menu = Menu::createWithArray(items);
    menu->setPosition(center.x, center.y);
    int space = 60;
    for(int i = 0; i < menu->getChildrenCount(); i++)
    {
        Node* temp = menu->getChildren().at(i);
        temp->setPosition(0, i * space);
    }
    this->addChild(menu, -1);

    //Close button
    closeButton = Button::create("icons/exit_unselected.png", "icons/exit_selected.png");
    closeButton->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
    std::cout << closeButton->getContentSize().width << " " << closeButton->getContentSize().height << std::endl;
    closeButton->setScale(visibleSize.height/3000);
    closeButton->setPosition(Vec2(visibleSize.width, 0));
    closeButton->addClickEventListener(CC_CALLBACK_0(onClick_closeButton, this));
    this->addChild(closeButton, -1);
    
    return true;
}

Scene* StartScene::createScene()
{
    return StartScene::create();
}

void StartScene::onClick_closeButton(Ref * pSender)
{
    Director::getInstance()->end();
}

void StartScene::onClick_startGameLabel(Ref* sender)
{
    std::cout << "Not implemented yet(" << std::endl;
}

void StartScene::onClick_goToSettings(Ref* sender)
{
    Director::getInstance()->replaceScene(SettingsScene::createScene());
}