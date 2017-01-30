#include "Vector2.h"

vector2::vector2()
{
  x_ = 0;
  y_ = 0;
  norme_ = 0;
}

vector2::vector2(float x, float y)
{
  x_ = x;
  y_ = y;
  norme_ = 0;
}

vector2::vector2(const vector2 &other)
{
  if (this != &other)
    {
      x_ = other.x_;
      y_ = other.y_;
      norme_ = other.norme_;
    }
}

vector2			vector2::operator=(const vector2 &other)
{
  if (this != &other)
    {
      x_ = other.x_;
      y_ = other.y_;
      norme_ = other.norme_;
    }
  return (*this);
}

vector2::~vector2()
{
  
}

float			vector2::getX() const
{
  return x_;
}

float			vector2::getY() const
{
  return y_;
}

float			vector2::getNorme() const
{
  return norme_;
}

void			vector2::setX(float x)
{
  x_ = x;
}

void			vector2::setY(float y)
{
  y_ = y;
}

void			vector2::setNorme(float norme)
{
  norme_ = norme;
}
