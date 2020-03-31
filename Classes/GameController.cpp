#include "GameController.h"

GameController::GameController(): generator(), distribution(1, 6)
{
    
}

void GameController::spawn()
{
    int rand = distribution(generator);
    switch (rand)
    {
    case 1:
        
        break;
    
    default:
        break;
    }
}