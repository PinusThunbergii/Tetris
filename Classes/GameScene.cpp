#include "GameScene.h"
#include "StartScene.h"
#include "Shape.h"

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

    box = Sprite::create("sprites/box.png");
    box->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    box->setPosition(center);
    box->setScale(0.2);
    this->addChild(box, -1);

    auto eventListenerKeyBoard = EventListenerKeyboard::create();
    eventListenerKeyBoard->onKeyPressed = CC_CALLBACK_2(GameScene::keyPressed, this);
    eventListenerKeyBoard->onKeyReleased = CC_CALLBACK_2(GameScene::keyReleased, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListenerKeyBoard, this);
    /*
    Shape I(4, 4, Color4F::MAGENTA,
    std::vector<std::vector<int>>{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 
    std::vector<std::vector<int>>{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}});
    */
    L.rotateClockwise();
    L.rotateClockwise();
    L.rotateClockwise();
    std::cout << "===========================" << std::endl;
    L.rotateCounterClockwise();
    L.rotateCounterClockwise();
    L.rotateCounterClockwise();

    fieldModel = new GameFieldModel(10, 20);
    fieldView = GameFieldView::createWithModel(fieldModel);
    fieldView->setModel(fieldModel);
    //fieldView->setPosition(Vec2(center.x, visibleSize.height));
    fieldView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    fieldView->setPosition(center);
    
    Size size = fieldView->getContentSize();
    std::cout << size.width << " " << size.height << std::endl;
    this->addChild(fieldView);
    this->scheduleUpdate();
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
    std::cout << (int)keyCode << std::endl;
    Vec2 dir;
    float deltaMove = 50;
    switch (keyCode)
    {

    case EventKeyboard::KeyCode::KEY_W:
        dir = Vec2(0, deltaMove);
        break;
    case EventKeyboard::KeyCode::KEY_A:
        dir = Vec2(-deltaMove, 0);
        break;
    case EventKeyboard::KeyCode::KEY_S:
        dir = Vec2(0, -deltaMove);
        break;
    case EventKeyboard::KeyCode::KEY_D:
        dir = Vec2(deltaMove, 0);
        break;
    default:
        return;
        //break;
    }
    auto mvb = MoveBy::create(0.5, dir);
    box->runAction(mvb);
}

void GameScene::keyReleased(EventKeyboard::KeyCode keyCode, Event *event)
{
    std::cout << (int)keyCode << std::endl;
}

void GameScene::update(float dt)
{
    std::cout << "Update interval: " << dt << std::endl;
    Vec2 boxPosition = box->getPosition();
    //if(boxPosition.x <= 0 || boxPosition.y <= 0)
}

