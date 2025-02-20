#pragma once
#include <random>
#include <iostream>
#include <chrono>
#include <queue>
#include "cocos2d.h"
#include "GameFieldModel.h"
#include "GameFieldView.h"
#include "Shape.h"

//#define SPAWN_ONLY_CUBE 

enum GameState{
    PAUSE,
    PLAY,
    STOP,
    GAMEOVER
};

class GameController
{
public:
    GameController();
    ~GameController();
    void Update();
    void Stop();
    void Start();
    void Pause();
    GameState GetGameState();
    void ProcessKeyPress(EventKeyboard::KeyCode keyCode);
    void Reset();
    int GetScore();
    void ConnectModel(GameFieldModel* model);
private:
    
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribution;
    std::queue<EventKeyboard::KeyCode> input_queue;
    std::chrono::time_point<std::chrono::system_clock> lastTime;
    GameFieldModel* model;
    Shape* current_figure;
    float updateInterval;
    int score;
    Shape* spawn();
    void drawShape(Shape* shape);
    void clearShape(Shape* shape);
    bool hasCollisionWithFieldBoard(Shape* shape);
    bool intersectWithFigures(Shape* shape);
    bool cantMoveDown(Shape* shape);
    bool cantMoveDownFirstSpawn(Shape* shape);
    void destroyFilledLines();
    bool moveLeft();
    bool moveRight();
    bool moveDown();
    void rotateClockwise();
    void rotateCounterClockwise();
    int checkFullRowLine();
    GameState state;
protected:  
};