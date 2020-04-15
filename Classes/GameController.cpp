#include "GameController.h"

GameController::GameController() : distribution(1, 7), model(nullptr),
                                   updateInterval(0.15f), current_figure(nullptr), score(0), state(GameState::PAUSE),
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
#ifdef SPAWN_ONLY_CUBE
    s = new Shape(O);
#else
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
#endif // SPAWN_ONLY_CUBE       
    s->setPositionX(model->getWidth() / 2);
    s->setPositionY(model->getHeight());
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
    if(state == GameState::PLAY)
    {
        if (current_figure == nullptr)
        {
            current_figure = spawn();
            if(cantMoveDownFirstSpawn(current_figure))
            {
                state = GameState::GAMEOVER; 
            }
        }
        

        clearShape(current_figure);
        auto now = std::chrono::system_clock::now();
        float delta = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTime).count() / 1000.f;

        if (delta >= updateInterval)
        {
            lastTime = now;
            /*if (cantMoveDown(current_figure))
            {
                state = GameState::GAMEOVER; 
            }*/
            if(!moveDown())
            {
                drawShape(current_figure);
                model->Update();
                delete current_figure;
                current_figure = nullptr;
                return;
            }
            
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
        int new_score_point = checkFullRowLine();
        score += new_score_point;
        if(new_score_point > 0)
        {
            updateInterval -= new_score_point / 1000.0f;
        }
        std::cout << score << std::endl;
        /*
        if (cantMoveDown(current_figure))
        {
            drawShape(current_figure);
            delete current_figure;
            current_figure = spawn();
        }
        */
        drawShape(current_figure);
        model->Update();
    }
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

bool GameController::moveLeft()
{
    Shape *tmp;
    tmp = new Shape(*current_figure);
    tmp->setPositionX(tmp->getPositionX() - 1);
    if (!hasCollisionWithFieldBoard(tmp) && !intersectWithFigures(tmp))
    {
        delete current_figure;
        current_figure = tmp;
        return true;
    }
    else
    {
        delete tmp;
        return false;
    }
}

bool GameController::moveRight()
{
    Shape *tmp;
    tmp = new Shape(*current_figure);
    tmp->setPositionX(tmp->getPositionX() + 1);
    if (!hasCollisionWithFieldBoard(tmp) && !intersectWithFigures(tmp))
    {
        delete current_figure;
        current_figure = tmp;
        return true;
    }
    else
    {
        delete tmp;
        return false;
    }
}

bool GameController::moveDown()
{
    Shape *tmp;
    tmp = new Shape(*current_figure);
    tmp->setPositionY(tmp->getPositionY() - 1);
    if (!hasCollisionWithFieldBoard(tmp) && !intersectWithFigures(tmp))
    {
        delete current_figure;
        current_figure = tmp;
        return true;
    }
    else
    {
        delete tmp;
        return false;
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

void GameController::Stop()
{
    state = GameState::STOP;
}

void GameController::Start()
{
    state = GameState::PLAY;
}

void GameController::Pause()
{
    state = GameState::PAUSE;
}

GameState GameController::GetGameState()
{
    return state;
}


bool GameController::cantMoveDownFirstSpawn(Shape* shape)
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
                if (x_i < 0 || x_i > model->getWidth() - 1 || y_i < 0 )
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

int GameController::checkFullRowLine()
{
    int destroyed_rows = 0;
    for (int y_i = 0; y_i < model->getHeight(); y_i++)
    {
        int checked_columns = 0;
        for (int x_i = 0; x_i < model->getWidth(); x_i++)
        {
            if((*model)(y_i, x_i) == 0) // if detect gap skip row
            {
                break;
            }
            else
            {
                checked_columns++;
            }
            
        }
        if(checked_columns == model->getWidth()) // detected full line
        {
            //clear that line
            /*for (int x_i = 0; x_i < model->getWidth(); x_i++)
            {
                (*model)(y_i, x_i) = 0;
            }*/

            for(int y_j = y_i + 1; y_j < model->getHeight(); y_j++)
            {
                for (int x_i = 0; x_i < model->getWidth(); x_i++)
                {
                    (*model)(y_j - 1, x_i) = (*model)(y_j, x_i);
                }
            }
            destroyed_rows++;
        }
    }
    return destroyed_rows;
}

int GameController::GetScore()
{
    return score;
}