#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class GameOverLayer: public Layer
{
public:
    GameOverLayer();
    GameOverLayer(int score);
    virtual bool init();
    static GameOverLayer* create();
    static GameOverLayer* createWithScore(int score);
private:
    Label* gameover;
    Label* scoreLabel;
    int score;

};