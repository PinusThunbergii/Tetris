#pragma once
#include "cocos2d.h"
#include <vector>
#include <iostream>
using namespace cocos2d;

//#define SHAPE_DEBUG

class Shape
{
public:
    Shape();
    Shape(int row_count, int column_count, int infill, 
        std::vector<std::vector<int>> mat, std::vector<std::vector<int>> wall_kick_data);
    Shape(const Shape& to_copy);  
    Shape& operator=(const Shape& s); 
    void rotateClockwise(); //+>
    void rotateCounterClockwise();//<+
    std::vector<std::vector<int>> getMatrix() const;
    int getMatrixRowCount() const;
    int getMatrixColumnCount() const;
    void setPositionX(int x_position);
    void setPositionY(int y_position);
    int getPositionX() const;
    int getPositionY() const;
    int getWidth() const;
    int getHeight() const;
private:
    int row_count;
    int column_count;
    //Color4F color;
    std::vector<std::vector<int>> mat;  // logical representation of figure
    std::vector<std::vector<int>> wall_kick_data;
    int x_position;
    int y_position;
    int rot_position;
    void print_2d_vec(std::vector<std::vector<int>> &vec);
    int infill;
protected:

};

 static Shape I(4, 4, 1,
    std::vector<std::vector<int>>{{0, 0, 0, 0}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}}, 
    std::vector<std::vector<int>>{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}});
    
 static Shape L(3, 3, 2,
    std::vector<std::vector<int>>{{0, 0, 1}, {1, 1, 1}, {0, 0, 0}}, 
    std::vector<std::vector<int>>{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}});

 static Shape J(3, 3, 3,
    std::vector<std::vector<int>>{{1, 0, 0}, {1, 1, 1}, {0, 0, 0}}, 
    std::vector<std::vector<int>>{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}});   

 static Shape O(2, 2, 4,
    std::vector<std::vector<int>>{{1, 1}, {1, 1}}, 
    std::vector<std::vector<int>>{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}});   

 static Shape S(3, 3, 5,
    std::vector<std::vector<int>>{{0, 1, 1}, {1, 1, 0}, {0, 0, 0}}, 
    std::vector<std::vector<int>>{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}});       

 static Shape Z(3, 3, 6,
    std::vector<std::vector<int>>{{1, 1, 0}, {0, 1, 1}, {0, 0, 0}}, 
    std::vector<std::vector<int>>{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}});   

 static Shape T(3, 3, 7,
    std::vector<std::vector<int>>{{0, 1, 0}, {1, 1, 1}, {0, 0, 0}}, 
    std::vector<std::vector<int>>{{0, 0}, {-2, 0}, {1, 0}, {-2, -1}, {1, 2}});       