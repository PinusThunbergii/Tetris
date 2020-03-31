#pragma once
#include <random>
#include "cocos2d.h"
#include "GameFieldModel.h"
#include "GameFieldView.h"

class GameController
{
public:
    GameController();
    void Update();
    void Stop();
    void ProcessKeyPress();
    void Reset();
    int GetScore();
private:
    void spawn();

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
protected:  
};