#include "GameController.h"

GameController::GameController() : distribution(1, 7), model(nullptr),
                                   updateInterval(0.1f), current_figure(nullptr), score(0),
                                   generator(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count())
{
    //current_figure = spawn();
    
}

GameController::~GameController()
{
}
Shape *GameController::spawn()
{
    int rand = distribution(generator);
    Shape *s;
    switch (rand)
    {
    case 1:
        s = new Shape(I);
        break;
    case 2:
        s = new Shape(J);
        break;
    case 3:
        s = new Shape(L);
        break;
    case 4:
        s = new Shape(O);
        break;
    case 5:
        s = new Shape(S);
        break;
    case 6:
        s = new Shape(T);
        break;
    case 7:
        s = new Shape(Z);
        break;
    default:
        std::cout << "Yellow submarine/////" << std::endl;
        return nullptr;
        break;
    }
    s->setPositionX(model->getWidth() / 2);
    s->setPositionY(model->getHeight()+2);
    return s;
}

void GameController::drawShape(Shape *shape)
{
    int shift_x = shape->getPositionX() - shape->getWidth() / 2;
    int shift_y = shape->getPositionY() - shape->getHeight() / 2;
    for (int y = 0; y < shape->getHeight(); y++)
    {
        for (int x = 0; x < shape->getWidth(); x++)
        {
            if (shape->getMatrix()[y][x] > 0)
            {
                int x_i = shift_x + x;
                int y_i = shift_y + y;
                (*model)(y_i, x_i) = shape->getMatrix()[y][x];
            }
        }
    }
}

void GameController::clearShape(Shape *shape)
{
    int shift_x = shape->getPositionX() - shape->getWidth() / 2;
    int shift_y = shape->getPositionY() - shape->getHeight() / 2;
    for (int y = 0; y < shape->getHeight(); y++)
    {
        for (int x = 0; x < shape->getWidth(); x++)
        {
            if (shape->getMatrix()[y][x] > 0)
            {
                int x_i = shift_x + x;
                int y_i = shift_y + y;
                (*model)(y_i, x_i) = 0;
            }
        }
    }
}

void GameController::ProcessKeyPress(EventKeyboard::KeyCode keyCode)
{
    input_queue.push(keyCode);
}

void GameController::ConnectModel(GameFieldModel *model)
{
    this->model = model;
}

void GameController::Update()
{

    if (current_figure == nullptr)
    {
        current_figure = spawn();
    }
    clearShape(current_figure);
    auto now = std::chrono::system_clock::now();
    float delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count() / 1000.f;

    if (delta >= updateInterval)
    {
        lastTime = now;
        moveDown();
    }

    while (!input_queue.empty())
    {
        EventKeyboard::KeyCode keyCode;
        keyCode = input_queue.back();
        input_queue.pop();

        switch (keyCode)
        {

        case EventKeyboard::KeyCode::KEY_W:
            rotateClockwise();
            break;
        case EventKeyboard::KeyCode::KEY_A:
            moveLeft();
            break;
        case EventKeyboard::KeyCode::KEY_S:
            rotateCounterClockwise();
            break;
        case EventKeyboard::KeyCode::KEY_D:
            moveRight();
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            moveDown();
            break;
        default:
            break;
        }
    }

    if (cantMoveDown(current_figure))
    {
        drawShape(current_figure);
        delete current_figure;
        current_figure = spawn();
    }

    drawShape(current_figure);
    model->Update();
}

bool GameController::hasCollisionWithFieldBoard(Shape *shape)
{
    int shift_x = shape->getPositionX() - shape->getWidth() / 2;
    int shift_y = shape->getPositionY() - shape->getHeight() / 2;
    for (int y = 0; y < shape->getHeight(); y++)
    {
        for (int x = 0; x < shape->getWidth(); x++)
        {
            if (shape->getMatrix()[y][x] > 0)
            {
                int x_i = shift_x + x;
                int y_i = shift_y + y;
                if (x_i < 0 || x_i > model->getWidth() - 1 || y_i < 0 || y_i > model->getHeight() + 2 )
                    return true;
            }
        }
    }
    return false;
}

bool GameController::intersectWithFigures(Shape* shape)
{
    int shift_x = shape->getPositionX() - shape->getWidth() / 2;
    int shift_y = shape->getPositionY() - shape->getHeight() / 2;
    for (int y = 0; y < shape->getHeight(); y++)
    {
        for (int x = 0; x < shape->getWidth(); x++)
        {
            if (shape->getMatrix()[y][x] > 0)
            {
                int x_i = shift_x + x;
                int y_i = shift_y + y;
                if (x_i < 0 || x_i > model->getWidth() - 1 || y_i < 0 || y_i > model->getHeight() + 2)
                    return true;
                if((*model)(y_i, x_i) > 0 )
                    return true;
            }
        }
    }
    return false;
}

bool GameController::cantMoveDown(Shape *shape)
{
    Shape *tmp = new Shape(*shape);
    tmp->setPositionY(tmp->getPositionY() - 1);
    int shift_x = tmp->getPositionX() - tmp->getWidth() / 2;
    int shift_y = tmp->getPositionY() - tmp->getHeight() / 2;
    for (int y = 0; y < tmp->getHeight(); y++)
    {
        for (int x = 0; x < tmp->getWidth(); x++)
        {
            if (tmp->getMatrix()[y][x] > 0)
            {
                int x_i = shift_x + x;
                int y_i = shift_y + y;
                if (x_i < 0 || x_i > model->getWidth() - 1 || y_i < 0 || y_i > model->getHeight() - 1)
                {
                    return true;
                }
                else if ((*model)(y_i, x_i) > 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void GameController::destroyFilledLines()
{
    for (int y = 0; y < model->getHeight(); y++)
    {
        for (int x = 0; x < model->getWidth(); x++)
        {
        }
    }
}

void GameController::moveLeft()
{
    Shape *tmp;
    tmp = new Shape(*current_figure);
    tmp->setPositionX(tmp->getPositionX() - 1);
    if (!hasCollisionWithFieldBoard(tmp) && !intersectWithFigures(tmp))
    {
        delete current_figure;
        current_figure = tmp;
    }
    else
    {
        delete tmp;
    }
}

void GameController::moveRight()
{
    Shape *tmp;
    tmp = new Shape(*current_figure);
    tmp->setPositionX(tmp->getPositionX() + 1);
    if (!hasCollisionWithFieldBoard(tmp) && !intersectWithFigures(tmp))
    {
        delete current_figure;
        current_figure = tmp;
    }
    else
    {
        delete tmp;
    }
}

void GameController::moveDown()
{
    Shape *tmp;
    tmp = new Shape(*current_figure);
    tmp->setPositionY(tmp->getPositionY() - 1);
    if (!hasCollisionWithFieldBoard(tmp) && !intersectWithFigures(tmp))
    {
        delete current_figure;
        current_figure = tmp;
    }
    else
    {
        delete tmp;
    }
}

void GameController::rotateClockwise()
{
    Shape *tmp;
    tmp = new Shape(*current_figure);
    tmp->rotateClockwise();
    if (!hasCollisionWithFieldBoard(tmp) && !intersectWithFigures(tmp))
    {
        delete current_figure;
        current_figure = tmp;
    }
    else
    {
        delete tmp;
    }
}

void GameController::rotateCounterClockwise()
{
    Shape *tmp;
    tmp = new Shape(*current_figure);
    tmp->rotateCounterClockwise();
    if (!hasCollisionWithFieldBoard(tmp) && !intersectWithFigures(tmp))
    {
        delete current_figure;
        current_figure = tmp;
    }
    else
    {
        delete tmp;
    }
}