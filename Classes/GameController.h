#pragma once
#include <random>
#include <iostream>
#include "cocos2d.h"
#include "GameFieldModel.h"
#include "GameFieldView.h"
#include "Shape.h"

class GameController
{
public:
    GameController();
    void Update();
    void Stop();
    void ProcessKeyPress(EventKeyboard::KeyCode keyCode);
    void Reset();
    int GetScore();
    void ConnectModel(GameFieldModel* model);
private:
    Shape spawn();
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
    GameFieldModel* model;
    Shape current_figure;
protected:  
};