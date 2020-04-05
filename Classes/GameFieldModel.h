#pragma once
#include <vector>
#include <random>
#include <iostream>
#include "cocos2d.h"

#include "GameFieldView.h"

//#define RAND_INFILL_TEST

class AbstractGameFieldView;

class GameFieldModel
{

public:
    GameFieldModel(int width, int height);
    ~GameFieldModel();
    int getHeight() const;
    void setHeight(int height);
    int getWidth() const;
    void setWidth(int width);
    int getHiddenRowsCount();
    int& operator()(size_t i, size_t j);
    std::vector<std::vector<int>> getField() const;
    void Update();
    void AddView(AbstractGameFieldView* observer);
    void NotifyView();
private:
    int width;
    int height;
    std::vector<std::vector<int>> logic_field;
    const int hidden_rows = 20;
    std::vector<AbstractGameFieldView*> observers;
protected:

};