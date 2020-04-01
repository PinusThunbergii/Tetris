#include "GameController.h"

GameController::GameController(): generator(), distribution(1, 7), model(nullptr)
{
    
}

Shape GameController::spawn()
{
    int rand = distribution(generator);
    Shape s;
    switch (rand)
    {
    case 1:
        s = I;
        return s;
        break;
    case 2:
        s = J;
        return s;
        break;
    case 3:
        s = L;
        return s;
        break;
    case 4:
        s = O;
        return s;
        break;
    case 5:
        s = S;
        return s;
        break;   
    case 6:
        s = T;
        return s;
        break; 
    case 7:
        s = Z;
        return s;
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
    auto mat = current_figure.getMatrix();

    for(int x = 0; x < row_count; x++)
    {
        for(int y = 0; y < column_count; y++)
        {
            int k = mat[x][y];
            std::cout << k << std::endl;
            (*model)(x, y) = k;
            //(*model)(x, y) = mat[x][y];
        }
    }
    model->Update();
}