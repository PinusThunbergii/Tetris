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
   
private:
    Menu* menu;
    Button* closeButton;
    static void onClick_closeButton(Ref* sender);
    static void onClick_startGameLabel(Ref* sender);
    static void onClick_goToSettings(Ref* sender);
protected:

};
