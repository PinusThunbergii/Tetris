#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class Shape: public Sprite
{
public:
    Shape();
    virtual ~Shape();
    static Shape* create(Vector<Vec2> mask, int size, Color4B color, const std::string& filename);
    void rotate();
private:
    Color4B color;
    int size;
    Vector<Vec2> mask;
    Vec2 position;
protected:

};

//const Shape I_shape;