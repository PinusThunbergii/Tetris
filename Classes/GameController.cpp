#include "GameController.h"

GameController::GameController() : generator(), distribution(1, 7), model(nullptr), 
    updateInterval(0.1f), current_figure(nullptr), score(0)
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
        return s;
        break;
    case 2:
        s = new Shape(J);
        return s;
        break;
    case 3:
        s = new Shape(L);
        return s;
        break;
    case 4:
        s = new Shape(O);
        return s;
        break;
    case 5:
        s = new Shape(S);
        return s;
        break;
    case 6:
        s = new Shape(T);
        return s;
        break;
    case 7:
        s = new Shape(Z);
        return s;
        break;
    default:
        std::cout << "Yellow submarine/////" << std::endl;
        return nullptr;
        break;
    }
}

bool GameController::can_spawn_down(Shape *figure)
{
    if (figure != nullptr)
    {

        int field_width = model->getWidth();
        int field_height = model->getHeight();
        int hidden_rows = model->getHiddenRowsCount();
    }
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
        current_figure->setPositionX(model->getWidth() / 2);
        current_figure->setPositionY(model->getHeight());
    }
    Shape *tmp;
    auto now = std::chrono::system_clock::now();
    float delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count() / 1000.f;
    clearShape(current_figure);
    if (delta >= updateInterval)
    {
        std::cout << "Update time " << delta << std::endl;
        lastTime = now;
        tmp = new Shape(*current_figure);
        tmp->setPositionY(tmp->getPositionY() - 1);
        if(cantMoveDown(tmp))
        {
            drawShape(current_figure);
            delete current_figure;
            current_figure = spawn();
            current_figure->setPositionX(model->getWidth() / 2);
            current_figure->setPositionY(model->getHeight());
            if(cantMoveDown(current_figure))
                std::cout << "game over" << std::endl;
           std::cout << "can`t move down" << std::endl;
        }
        else if (!hasCollisionWithFlieldBoard(tmp))
        {

            delete current_figure;
            current_figure = tmp;
        }
        else
        {
            delete tmp;
        }
        /*
        if(cantMoveDown(tmp))
        {
            
            delete current_figure;
            current_figure = spawn();
            current_figure->setPositionX(model->getWidth() / 2);
            current_figure->setPositionY(model->getHeight() / 2);
            
           std::cout << "can`t move down" << std::endl;
        }
        */
    }

    
    while (!input_queue.empty())
    {
        EventKeyboard::KeyCode keyCode;
        keyCode = input_queue.back();
        input_queue.pop();

        switch (keyCode)
        {

        case EventKeyboard::KeyCode::KEY_W:
            tmp = new Shape(*current_figure);
            tmp->rotateClockwise();
            if (!hasCollisionWithFlieldBoard(tmp))
            {
                delete current_figure;
                current_figure = tmp;
            }
            else
            {
                delete tmp;
            }

            //current_figure->rotateClockwise();
            break;
        case EventKeyboard::KeyCode::KEY_A:
            tmp = new Shape(*current_figure);
            tmp->setPositionX(tmp->getPositionX() - 1);
            if (!hasCollisionWithFlieldBoard(tmp))
            {
                delete current_figure;
                current_figure = tmp;
            }
            else
            {
                delete tmp;
            }
            //current_figure->setPositionX(current_figure->getPositionX() - 1);
            break;
        case EventKeyboard::KeyCode::KEY_S:
            tmp = new Shape(*current_figure);
            tmp->rotateCounterClockwise();
            if (!hasCollisionWithFlieldBoard(tmp))
            {
                delete current_figure;
                current_figure = tmp;
            }
            else
            {
                delete tmp;
            }
            //current_figure->rotateCounterClockwise();
            break;
        case EventKeyboard::KeyCode::KEY_D:
            tmp = new Shape(*current_figure);
            tmp->setPositionX(tmp->getPositionX() + 1);
            if (!hasCollisionWithFlieldBoard(tmp))
            {
                delete current_figure;
                current_figure = tmp;
            }
            else
            {
                delete tmp;
            }
            //current_figure->setPositionX(current_figure->getPositionX() + 1);
            break;
        case EventKeyboard::KeyCode::KEY_SPACE:
            tmp = new Shape(*current_figure);
            tmp->setPositionY(tmp->getPositionY() - 1);
            if (!hasCollisionWithFlieldBoard(tmp))
            {
                delete current_figure;
                current_figure = tmp;
            }
            else
            {
                delete tmp;
            }
            //current_figure->setPositionY(current_figure->getPositionY() - 1);
            break;
        default:
            return;
            //break;
        }
    }
    drawShape(current_figure);

    model->Update();
}

bool GameController::hasCollisionWithFlieldBoard(Shape *shape)
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
                //(*model)(y_i, x_i) = shape->getMatrix()[y][x];
            }
        }
    }
    return false;
}

bool GameController::cantMoveDown(Shape *shape)
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
    for(int y = 0; y < model->getHeight(); y++)
    {
        for(int x = 0; x < model->getWidth(); x++)
        {
            
        }
    }
}
