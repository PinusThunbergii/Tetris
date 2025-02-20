#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "StartScene.h"
#include "GameFieldView.h"
#include "GameFieldModel.h"
#include "GameController.h"
#include "GameOverLayer.h"

using namespace cocos2d;
using namespace cocos2d::ui;

class GameScene: public Scene
{
public:
    virtual bool init();
    static Scene* createScene();
    void update(float dt);
    CREATE_FUNC(GameScene);
    ~GameScene();
private:
    Button* backButton;
    Sprite* box;
    Label* score;
    static void onClick_backButton(Ref *sender);
    void keyPressed(EventKeyboard::KeyCode keyCode, Event* event);
    void keyReleased(EventKeyboard::KeyCode keyCode, Event* event);
    GameFieldView* fieldView;
    GameFieldModel* fieldModel;
    GameController* controller;
    GameOverLayer* gameoverLayer;
    Vec2 center;
    Vec2 origin;
    Size visibleSize;
};