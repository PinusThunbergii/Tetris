#include "Shape.h"

Shape::Shape(int row_count, int column_count, Color4F color, 
    std::vector<std::vector<int>> mat, std::vector<std::vector<int>> wall_kick_data):
    x_position(0), y_position(0), row_count(row_count), 
    column_count(column_count), mat(mat), wall_kick_data(wall_kick_data), color(color)
{

}

void Shape::rotateClockwise()
{
    // maybe should use mod ???
    rot_position++;
    if(rot_position > 3)
        rot_position = 0;

#ifdef SHAPE_DEBUG
    print_2d_vec(mat);
#endif // SHAPE_DEBUG

    if(row_count == column_count) // if square
    {
        std::vector<std::vector<int>> new_mat;
        new_mat.resize(row_count);
        for(int i = 0; i < row_count; i++)
            new_mat[i].resize(column_count);

        for(int i = 0; i < row_count; i++)
        {
            for(int j = 0; j < column_count; j++)
            {
                new_mat[j][row_count - i - 1] = mat[i][j];
            }
        }
        mat = new_mat;
    }

#ifdef SHAPE_DEBUG
    print_2d_vec(mat);
#endif // SHAPE_DEBUG
}

void Shape::rotateCounterClockwise()
{
    rot_position--;
    if(rot_position < 0)
        rot_position = 3;

#ifdef SHAPE_DEBUG
    print_2d_vec(mat);
#endif // SHAPE_DEBUG

    if(row_count == column_count) // if square
    {
        std::vector<std::vector<int>> new_mat;
        new_mat.resize(row_count);
        for(int i = 0; i < row_count; i++)
            new_mat[i].resize(column_count);

        for(int i = 0; i < row_count; i++)
        {
            for(int j = 0; j < column_count; j++)
            {
                //new_mat[j][row_count - i - 1] = mat[i][j];
                new_mat[i][j] = mat[j][row_count - i - 1];
            }
        }
        mat = new_mat;
    }
    
#ifdef SHAPE_DEBUG
    print_2d_vec(mat);
#endif // SHAPE_DEBUG
}

void Shape::print_2d_vec(std::vector<std::vector<int>> &vec)
{
    std::cout << "---------------------------" << std::endl;
    for(auto iter = vec.begin(); iter != vec.end(); iter++)
    {
        for(auto iter_ = iter->begin(); iter_ != iter->end(); iter_++)
        {
            std::cout << *(iter_) << " ";
        }
        std::cout << std::endl;
    }
}


std::vector<std::vector<int>> Shape::getMatrix() const
{
    return mat;
}

int Shape::getMatrixRowCount() const
{
    return row_count;
}

int Shape::getMatrixColumnCount() const
{
    return column_count;
}

void Shape::setPositionX(int x_position)
{
    this->x_position = x_position;
}

void Shape::setPositionY(int y_position)
{
    this->y_position = y_position;
}

int Shape::getPositionX() const
{
    return x_position;
}

int Shape::getPositionY() const
{
    return y_position;
}
