#pragma once
#include "cocos2d.h"
#include "GameFieldModel.h"
#include <iostream>

using namespace cocos2d;

class GameFieldView: public Node
{
public:
    virtual bool init();
    //CREATE_FUNC(GameFieldView);
    static GameFieldView* createWithModel(GameFieldModel* pModel);
    void update(float dt);
    void setModel(GameFieldModel* pModel);
protected:

private:
    GameFieldModel* pFieldModel;
    void drawField();
    GameFieldView();
    GameFieldView(GameFieldModel* pModel);
    int cell_size;
    int borderWidth;
    Color4F borderColor;
    Color4F infillColor;
};