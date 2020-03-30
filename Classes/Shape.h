#pragma once
#include "cocos2d.h"
#include <vector>

using namespace cocos2d;

class Shape
{
public:
    Shape();
    void rotateClockwise(); //+>
    void rotateCounterClockwise();//<+
private:
    int row_count;
    int column_count;
    Color4F color;
    std::vector<std::vector<int>> mat;  
    int x_position;
    int y_position;
protected:

};

