#include "GameOverLayer.h"

GameOverLayer::GameOverLayer()
{

}

GameOverLayer::GameOverLayer(int score) : score(score)
{
    
}


GameOverLayer* GameOverLayer::create()
{
    GameOverLayer *pRet = new GameOverLayer();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = nullptr;
    }
    return pRet;
}

GameOverLayer* GameOverLayer::createWithScore(int score)
{
    GameOverLayer *pRet = new GameOverLayer(score);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = nullptr;
    }
    return pRet;
}


bool GameOverLayer::init() 
{
    if(!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 center = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    gameover = Label::createWithTTF("GAME OVER", "fonts/Marker Felt.ttf", 100.0f);
    gameover->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    gameover->setPosition(center);
    this->addChild(gameover);

    std::string score_str("You score: ");
    scoreLabel = Label::createWithTTF(score_str + std::to_string(score), "fonts/Marker Felt.ttf", 40.0f);
    scoreLabel->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    scoreLabel->setPosition(Vec2(center.x, center.y - 100.0f));
    this->addChild(scoreLabel);

    return true;
}


