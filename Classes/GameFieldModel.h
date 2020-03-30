#pragma once
#include "cocos2d.h"
#include <vector>

class GameFieldModel
{

public:
    GameFieldModel(int width, int height);
    ~GameFieldModel();
    int getHeight() const;
    void setHeight(int height);
    int getWidth() const;
    void setWidth(int width);
private:
    int width;
    int height;
    std::vector<std::vector<int>> logic_field;
protected:

};