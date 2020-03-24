#pragma once
#include <array>
#include "cocos2d.h"

using namespace cocos2d;

template<int width, int height>
class Figure
{
public:
    Figure(std::array<std::array<int, width>, height> mask, Color4B color);
    Figure(const Figure & toCopy);
    void rotateLeft();
    void rotateRight();

private:
    std::array<std::array<int, width>, height> mask;
    Color4B color;
    int coord_x;
    int coord_y;
};