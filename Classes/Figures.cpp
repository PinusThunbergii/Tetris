#include "Figures.h"

template<int width, int height>
Figure<width, height>
::Figure(std::array<std::array<int, width>, height> mask, Color4B color)
{
    this->mask = mask;
    this->color = color;
    this->coord_x = 0;
    this->coord_y = 0;
}


template<int width, int height>
Figure<width, height>
::Figure(const Figure & toCopy)
{
    this->mask = toCopy.mask;
    this->color = toCopy.color;
    this->coord_x = 0;
    this->coord_y = 0;
}

template<int width, int height>
void Figure<width, height>::rotateLeft()
{
    //for(auto iter_x = mask.begin(); iter )
}
