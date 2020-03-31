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
    //CREATE_FUNC(GameFieldView);
    static GameFieldView* create();
    //static GameFieldView* createWithModel(GameFieldModel* pModel);
    void updateView(GameFieldModel* model);
    void update(float dt);
    //void setModel(GameFieldModel* pModel);
protected:

private:
    //GameFieldModel* pFieldModel;
    void drawField(GameFieldModel* pFieldModel);
    GameFieldView();
    //GameFieldView(GameFieldModel* pModel);
    int cell_size;
    int borderWidth;
    Color4F borderColor;
    Color4F infillColor;
};