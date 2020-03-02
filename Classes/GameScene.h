#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class GameScene: public Scene
{
public:
    virtual bool init();
    static Scene* createScene();
    CREATE_FUNC(GameScene);
private:
    Button* backButton;
    static void onClick_backButton(Ref *sender);
};