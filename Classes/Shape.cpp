#include "Shape.h"

 Shape::Shape()
{

}

 Shape::~Shape()
{

}

Shape* Shape::create(Vector<Vec2> mask, int size, Color4B color, const std::string& filename)
{
    auto p = new Shape();
    if(p && p->initWithFile(filename))
    {
        p->autorelease();
        return p;
    }
    CC_SAFE_RELEASE(p);
    return nullptr;
}