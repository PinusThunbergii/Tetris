#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class SettingsScene: public Scene
{
public:
    static Scene *createScene();
    virtual bool init();
    void onClick_checkBox(Ref* sender, Widget::TouchEventType type);
    CREATE_FUNC(SettingsScene);
private:
    Button* closeButton;
    Button* backButton;
    Layer* settingsMenu;
    CheckBox* displayModeCheckBox;
    static void onClick_closeButton(Ref* sender);
    static void onClick_backButton(Ref* sender);
    GLViewImpl *view;
};
