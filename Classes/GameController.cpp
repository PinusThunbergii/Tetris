#include "GameController.h"

GameController::GameController(): generator(), distribution(1, 6), model(nullptr)
{
    
}

Shape GameController::spawn()
{
    int rand = distribution(generator);
    switch (rand)
    {
    case 1:
        return I;
        break;
    case 2:
        return J;
        break;
    case 3:
        return L;
        break;
    case 4:
        return O;
        break;
    case 5:
        return S;
        break;   
    case 6:
        return T;
        break; 
    case 7:
        return Z;
        break;             
    default:
        std::cout << "Yellow submarine/////" << std::endl;
        break;
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

void GameController::ConnectModel(GameFieldModel* model)
{
    this->model = model;
}


void GameController::Update()
{
    current_figure = spawn();
    current_figure.setPositionX(5);
    current_figure.setPositionY(10);

    int row_count = current_figure.getHeight();
    int column_count = current_figure.getWidth();

    for(int x = 0; x < row_count; x++)
    {
        for(int y = 0; y < column_count; y++)
        {
            (*model)(x, y) = current_figure.getMatrix()[x][y];
        }
    }
    model->Update();
}