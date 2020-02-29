#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <iostream>

using namespace cocos2d;
using namespace ui;
class StartScene: public Scene
{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(StartScene);

    void onClick(Ref* pSender, Widget::TouchEventType type);
    void toggleCheckbox(Ref* pSender, Widget::TouchEventType type);
    void update(float dt);
private:
    Sprite* sprite;
    CheckBox* checkBox;
    bool isFullScreen;
    Size screenSize;
    Menu menu;
protected:

};
