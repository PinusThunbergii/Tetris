#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class SettingsScene: public Scene
{
private:
    
public:
    static Scene *createScene();
    virtual bool init();
    CREATE_FUNC(SettingsScene);
};
