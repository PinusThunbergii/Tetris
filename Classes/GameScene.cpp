#include "GameScene.h"

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

    visibleSize = Director::getInstance()->getVisibleSize();
    center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    origin = Director::getInstance()->getVisibleOrigin();

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
    //fieldModel = new GameFieldModel(20, 40);
    fieldView = GameFieldView::create();
    fieldView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    fieldView->setPosition(center);
    fieldModel->AddView(fieldView);
    fieldModel->Update();
    controller->ConnectModel(fieldModel);
    this->addChild(fieldView);

    score = Label::createWithTTF("", "fonts/Marker Felt.ttf", 40.0f);
    score->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    score->setPosition(Vec2(0.0f, center.y));
    this->addChild(score);

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
    std::string score_str("Score: ");
    int score_num = controller->GetScore();
    score_str += std::to_string(score_num);
    score->setString(score_str);
    if(controller->GetGameState() == GameState::GAMEOVER)  
    {
        std::cout << "Gameover" << std::endl;
        gameoverLayer = GameOverLayer::createWithScore(score_num);
        this->addChild(gameoverLayer);
        this->unscheduleUpdate();
    } 
}

