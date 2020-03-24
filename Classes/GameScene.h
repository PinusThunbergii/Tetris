#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameFieldView.h"
#include "GameFieldModel.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class GameScene: public Scene
{
public:
    virtual bool init();
    static Scene* createScene();
    void update(float dt);
    CREATE_FUNC(GameScene);
private:
    Button* backButton;
    Sprite* box;
    static void onClick_backButton(Ref *sender);
    void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void keyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    GameFieldView* fieldView;
    GameFieldModel* fieldModel;
};