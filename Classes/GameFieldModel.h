#pragma once
#include "cocos2d.h"
#include <vector>
#include <random>
#include <iostream>

class GameFieldModel
{

public:
    GameFieldModel(int width, int height);
    ~GameFieldModel();
    int getHeight() const;
    void setHeight(int height);
    int getWidth() const;
    void setWidth(int width);
    int& operator()(size_t i, size_t j);
    std::vector<std::vector<int>> getField() const;
private:
    int width;
    int height;
    std::vector<std::vector<int>> logic_field;
    const int hidden_rows = 2;
protected:

};