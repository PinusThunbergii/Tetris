#include "GameScene.h"
#include "StartScene.h"
#include "Shape.h"

GameScene::~GameScene()
{
    if(fieldModel != nullptr)
        delete fieldModel;
    if(controller != nullptr)
        delete controller;    
}

bool GameScene::init()
{
    if (!Scene::init())
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

    auto eventListenerKeyBoard = EventListenerKeyboard::create();
    eventListenerKeyBoard->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
    eventListenerKeyBoard->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListenerKeyBoard, this);
    
    controller = new GameController();
    fieldModel = new GameFieldModel(10, 20);
    fieldView = GameFieldView::create();
    fieldView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    fieldView->setPosition(center);
    fieldModel->AddView(fieldView);
    fieldModel->Update();
    controller->ConnectModel(fieldModel);
    this->addChild(fieldView);

    this->scheduleUpdate();
    controller->Start();
    return true;
}

Scene *GameScene::createScene()
{
    return GameScene::create();
}

void GameScene::onClick_backButton(Ref *sender)
{
    Director::getInstance()->replaceScene(StartScene::create());
}

void GameScene::keyPressed(EventKeyboard::KeyCode keyCode, Event *event)
{
   controller->ProcessKeyPress(keyCode);
   if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
   {
        if(controller->GetGameState() == GameState::PAUSE)  
        {
            controller->Start();
        } 
        else if(controller->GetGameState() == GameState::PLAY)
        {
            controller->Pause(); 
        }    
   }

}

void GameScene::keyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    //std::cout << (int)keyCode << std::endl;
}

void GameScene::update(float dt)
{
    controller->Update();
    if(controller->GetGameState() == GameState::GAMEOVER)  
    {
        std::cout << "Gameover" << std::endl;
    } 
}

