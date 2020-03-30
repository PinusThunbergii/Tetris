#include "GameFieldModel.h"

GameFieldModel::GameFieldModel(int width, int height)
{
    this->width = width;
    this->height = height;
    logic_field.clear();
    logic_field.resize(size_t(height));
    for (size_t i = 0; i < height; i++)
    {
        logic_field.clear();
        logic_field[i].resize(size_t(width));
    }
}

int GameFieldModel::getHeight() const
{
    return this->height;
}

void GameFieldModel::setHeight(int height)
{
    this->height= height;
    logic_field.clear();
    logic_field.resize(size_t(height));
    for (size_t i = 0; i < height; i++)
    {
        logic_field.clear();
        logic_field[i].resize(size_t(width));
    }
}

int GameFieldModel::getWidth() const
{
    return this->width;
}

void GameFieldModel::setWidth(int width)
{
    for (size_t i = 0; i < height; i++)
    {
        logic_field.clear();
        logic_field[i].resize(size_t(width));
    }
}

GameFieldModel::~GameFieldModel()
{

}