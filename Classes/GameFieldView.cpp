#include "GameFieldView.h"

GameFieldView::GameFieldView(): 
    cell_size(20), borderWidth(1), 
    borderColor(Color4F::BLUE), infillColor(Color4F(0.0f, 0.0f, 0.0f, 0.0f))
{
}

GameFieldView::GameFieldView(GameFieldModel *pModel): GameFieldView()
{
    this->setModel(pModel);
    int column_count = pFieldModel->getWidth();
    int row_count = pFieldModel->getHeight();
    Size view_size(float(column_count * cell_size), float(row_count * cell_size));
    this->setContentSize(view_size);
}

GameFieldView *GameFieldView::createWithModel(GameFieldModel *pModel)
{
    GameFieldView *pRet = new (std::nothrow) GameFieldView(pModel);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}
bool GameFieldView::init()
{
    //Super init
    if (!Node::init())
    {
        return false;
    }

    drawField();
    this->scheduleUpdate();
    return true;
}

void GameFieldView::update(float dt)
{
    std::cout << "GameFieldView::update" << std::endl;
}

void GameFieldView::setModel(GameFieldModel *pModel)
{
    if (pModel != nullptr)
    {
        this->pFieldModel = pModel;
    }
    else
    {
        /* code */
    }
}

void GameFieldView::drawField()
{
    int column_count = pFieldModel->getWidth();
    int row_count = pFieldModel->getHeight();

    auto rectNode = DrawNode::create();
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
            switch((*pFieldModel)(y, x)) 
            {
                case 1:
                    currentInfillColor = Color4F::MAGENTA;
                    break;
                case 2:
                    currentInfillColor = Color4F::GRAY;
                    break;
                case 3:
                    currentInfillColor = Color4F::GREEN;
                    break;
                case 4:
                    currentInfillColor = Color4F::YELLOW;
                    break;
                case 5:
                    currentInfillColor = Color4F::ORANGE;
                    break;
                case 6:
                    currentInfillColor = Color4F::RED;
                    break;                
                default:
                    currentInfillColor = this->infillColor;
                    break;
            }
            rectNode->drawPolygon(rectangle, 4, currentInfillColor, borderWidth, borderColor);
        }
    }
    this->addChild(rectNode);
}