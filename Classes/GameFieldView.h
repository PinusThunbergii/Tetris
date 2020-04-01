#pragma once
#include "cocos2d.h"
#include <iostream>

#include "GameFieldModel.h"

using namespace cocos2d;

class GameFieldModel;

class AbstractGameFieldView
{
public:
    virtual void updateView(GameFieldModel* model) = 0;
};

class GameFieldView: public Node, public AbstractGameFieldView
{
public:
    virtual bool init();
    static GameFieldView* create();
    void updateView(GameFieldModel* model);
    void update(float dt);
protected:

private:
    void drawField(GameFieldModel* pFieldModel);
    GameFieldView();
    int cell_size;
    int borderWidth;
    Color4F borderColor;
    Color4F infillColor;
    DrawNode* rectNode;
};