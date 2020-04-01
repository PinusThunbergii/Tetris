#include "Shape.h"

Shape::Shape()
{
    
}

Shape::Shape(int row_count, int column_count, int infill, 
    std::vector<std::vector<int>> mat, std::vector<std::vector<int>> wall_kick_data):
    x_position(0), y_position(0), row_count(row_count), 
    column_count(column_count), mat(mat), wall_kick_data(wall_kick_data), infill(infill)
{
    for(int i = 0; i < row_count; i++)
    {
        for(int j = 0; j < column_count; j++)
        {
            if(this->mat[i][j])
                this->mat[i][j] = infill;
        }
    }
}

Shape& Shape::operator=(const Shape& s)
{
    this->mat = s.mat;
    this->wall_kick_data = s.wall_kick_data;
    this->x_position = s.x_position;
    this->y_position = s.y_position;
    this->rot_position = s.rot_position;
    this->row_count = s.row_count;
    this->column_count = s.column_count;
    this->infill = s.infill;
    return *this;
}

Shape::Shape(const Shape& to_copy)
{
    this->mat = to_copy.mat;
    this->wall_kick_data = to_copy.wall_kick_data;
    this->x_position = to_copy.x_position;
    this->y_position = to_copy.y_position;
    this->rot_position = to_copy.rot_position;
    this->row_count = to_copy.row_count;
    this->column_count = to_copy.column_count;
    this->infill = to_copy.infill;

}

void Shape::rotateClockwise()
{
    // maybe should use mod ???
    rot_position++;
    if(rot_position > 3)
        rot_position = 0;

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
    std::cout << rot_position << std::endl;
#endif // SHAPE_DEBUG
}

void Shape::rotateCounterClockwise()
{
    rot_position--;
    if(rot_position < 0)
        rot_position = 3;

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
    std::cout << rot_position << std::endl;
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

int Shape::getWidth() const
{
    return column_count;
}

int Shape::getHeight() const
{
    return row_count;
}