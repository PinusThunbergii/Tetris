#include "GameFieldView.h"

GameFieldView::GameFieldView(): 
    cell_size(35), borderWidth(0.5), 
    borderColor(Color4F::GRAY), infillColor(Color4F(0.0f, 0.0f, 0.0f, 0.0f))
{
}

GameFieldView *GameFieldView::create()
{
    GameFieldView *pRet = new (std::nothrow) GameFieldView();
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        delete pRet;
        pRet = nullptr;
    }
    return pRet;
}

bool GameFieldView::init()
{
    //Super init
    if (!Node::init())
    {
        return false;
    }
    rectNode = DrawNode::create();
    //drawField();
    this->addChild(rectNode);
    this->scheduleUpdate();
    return true;
}

void GameFieldView::update(float dt)
{
    //5std::cout << "GameFieldView::update" << std::endl;
}

void GameFieldView::drawField(GameFieldModel* pFieldModel)
{
    int column_count = pFieldModel->getWidth();
    int row_count = pFieldModel->getHeight();

    //auto rectNode = DrawNode::create();
    rectNode->clear();
    Color4F currentInfillColor;

    for (int y = 0; y < row_count; y++)
    {
        for (int x = 0; x < column_count; x++)
        {
            Vec2 rectangle[4];
            rectangle[0] = Vec2(x * cell_size, y * cell_size);
            rectangle[1] = Vec2(x * cell_size + cell_size, y * cell_size);
            rectangle[2] = Vec2(x * cell_size + cell_size, y * cell_size + cell_size);
            rectangle[3] = Vec2(x * cell_size, y * cell_size + cell_size);
            int c = (*pFieldModel)(y, x);
            switch(c) 
            {
                case 1:
                    currentInfillColor = Color4F(0.0f, 1.0f, 1.0f, 1.0f);
                    break;
                case 2:
                    currentInfillColor = Color4F::ORANGE;
                    break;
                case 3:
                    currentInfillColor = Color4F::BLUE;
                    break;
                case 4:
                    currentInfillColor = Color4F::YELLOW;
                    break;
                case 5:
                    currentInfillColor = Color4F::GREEN;
                    break;
                case 6:
                    currentInfillColor = Color4F::RED;
                    break;
                case 7:
                    currentInfillColor = Color4F::MAGENTA;
                    break;                                   
                default:
                    currentInfillColor = this->infillColor;
                    break;
            }
            rectNode->drawPolygon(rectangle, 4, currentInfillColor, borderWidth, borderColor);
        }
    }
   //this->addChild(rectNode);
}

void GameFieldView::updateView(GameFieldModel* model)
{
    int column_count = model->getWidth();
    int row_count = model->getHeight();
    Size view_size(float(column_count * cell_size), float(row_count * cell_size));
    this->setContentSize(view_size);
    drawField(model);
}