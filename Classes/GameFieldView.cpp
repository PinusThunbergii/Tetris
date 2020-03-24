#include "GameFieldView.h"

GameFieldView::GameFieldView()
{
}
GameFieldView::GameFieldView(GameFieldModel *pModel)
{
    this->setModel(pModel);
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
    if (!Layer::init())
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
    int borderWidth = 1;
    Color4F borderColor = Color4F::BLUE;
    Color4F infillColor = Color4F(0.0f, 0.0f, 0.0f, 0.0f);
    int width = pFieldModel->getWidth();
    int heigth = pFieldModel->getHeight();
    int cell_size = 10;

    auto rectNode = DrawNode::create();
    /*Vec2 rectangle[4];
    rectangle[0] = Vec2(0, 0);
    rectangle[1] = Vec2(100, 0);
    rectangle[2] = Vec2(100, 100);
    rectangle[3] = Vec2(0, 100);*/

    //rectNode->drawPolygon(rectangle, 4, Color4F::BLACK, 3, Color4F::MAGENTA);
    for (int y = 0; y < heigth; y++)
    {
        for (int x = 0; x < width; x++)
        {
            Vec2 rectangle[4];
            rectangle[0] = Vec2(x * cell_size, y * cell_size);
            rectangle[1] = Vec2(x * cell_size + cell_size, y * cell_size);
            rectangle[2] = Vec2(x * cell_size + cell_size, y * cell_size + cell_size);
            rectangle[3] = Vec2(x * cell_size, y * cell_size + cell_size);
            rectNode->drawPolygon(rectangle, 4, infillColor, borderWidth, borderColor);
        }
    }
    this->addChild(rectNode);
}