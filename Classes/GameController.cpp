#include "GameController.h"

GameController::GameController() : generator(), distribution(1, 7), model(nullptr), updateInterval(0.8f), current_figure(nullptr)
{
    //current_figure = spawn();
}


GameController::~GameController() 
{
    
}
Shape* GameController::spawn()
{
    int rand = distribution(generator);
    Shape* s;
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


bool GameController::can_spawn_down(Shape* figure) 
{
    if(figure != nullptr)
    {
        
        int field_width = model->getWidth();
        int field_height = model->getHeight();
        int hidden_rows = model->getHiddenRowsCount();
        
    }
}

void GameController::drawShape(Shape* shape)
{
    int shift_x = shape->getPositionX() - shape->getWidth() / 2;
    int shift_y = shape->getPositionY() - shape->getHeight() / 2;
    for(int y = 0; y < shape->getHeight(); y++)
    {
        for(int x = 0; x < shape->getWidth(); x++)
        {
            if(shape->getMatrix()[y][x] > 0)
            {
                int x_i = shift_x + x;
                int y_i = shift_y + y;
                (*model)(y_i, x_i) = shape->getMatrix()[y][x];
            }
        }
    }
}

void GameController::clearShape(Shape* shape)
{
    int shift_x = shape->getPositionX() - shape->getWidth() / 2;
    int shift_y = shape->getPositionY() - shape->getHeight() / 2;
    for(int y = 0; y < shape->getHeight(); y++)
    {
        for(int x = 0; x < shape->getWidth(); x++)
        {
            if(shape->getMatrix()[y][x] > 0)
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
    switch (keyCode)
    {

    case EventKeyboard::KeyCode::KEY_W:

        break;
    case EventKeyboard::KeyCode::KEY_A:

        break;
    case EventKeyboard::KeyCode::KEY_S:

        break;
    case EventKeyboard::KeyCode::KEY_D:

        break;
    default:
        return;
        //break;
    }
}

void GameController::ConnectModel(GameFieldModel *model)
{
    this->model = model;
}

void GameController::Update()
{
    if(current_figure != nullptr)
    {

    }
    else
    {
        current_figure = spawn();
        current_figure->setPositionX(model->getWidth() / 2);
        current_figure->setPositionY(model->getHeight()+4);
    }
    

    auto now = std::chrono::system_clock::now();
    float delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count() / 1000.f;
    if (delta >= updateInterval)
    {
        std::cout << "Update time " << delta << std::endl;
        lastTime = now;
        static int t = 0;
        //drawShape(current_figure);
        if(t < 20)
        {
            clearShape(current_figure);
            current_figure->setPositionY(current_figure->getPositionY() - 1);
            current_figure->rotateClockwise();
            drawShape(current_figure);
            t++;
        }
        
        model->Update();
    }
    
}