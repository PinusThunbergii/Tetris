#include "GameFieldModel.h"

GameFieldModel::GameFieldModel(int width, int height)
{
    this->width = width;
    this->height = height + hidden_rows; //add hidden rows
    logic_field.clear();
    logic_field.resize(size_t(this->height));
    for (size_t i = 0; i < this->height; i++)
    {
        //logic_field.clear();
        logic_field[i].resize(size_t(this->width));
    }
#ifdef RAND_INFILL_TEST
    std::default_random_engine generator(3);
    std::uniform_int_distribution<int> distribution(1,6);
    
    for (size_t i = 0; i < this->height-hidden_rows; i++)
    {
        for (size_t j = 0; j < this->width; j++)
        {
            logic_field[i][j] = distribution(generator);
            std::cout << logic_field[i][j] << " ";
        }
        std::cout << std::endl;
    }
#endif // DEBUG    
    
}

GameFieldModel::~GameFieldModel()
{

}

int GameFieldModel::getHeight() const
{
    return this->height-hidden_rows;
}

void GameFieldModel::setHeight(int height)
{
    this->height= height+hidden_rows;
    logic_field.clear();
    logic_field.resize(size_t(this->height));
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


int GameFieldModel::getHiddenRowsCount() 
{
    return hidden_rows;
}
int& GameFieldModel::operator()(size_t i, size_t j)
{
    //if(i >= 0 && i < width && j >= 0 && j < height)
    return logic_field[i][j]; 
}

std::vector<std::vector<int>> GameFieldModel::getField() const
{
    return logic_field;
}

void GameFieldModel::Update()
{
    NotifyView();
}

void GameFieldModel::AddView(AbstractGameFieldView* observer)
{
    observers.push_back(observer);
}

void GameFieldModel::NotifyView()
{
    for(auto iter = observers.begin(); iter != observers.end(); iter++)
    {
        if((*iter) != nullptr)
            (*iter)->updateView(this);
    }
}