#ifndef VECTOR2_HH
# define VECTOR2_HH

#include <utility>

class	vector2
{
  float			x_;
  float			y_;
  float			norme_;
  
public:
  vector2();
  vector2(float x, float y);
  vector2(const vector2 &other);
  vector2	operator=(const vector2 &other);
  ~vector2();

  float			getX() const;
  float			getY() const;
  float			getNorme() const;

  void			setX(float x);
  void			setY(float y);
  void			setNorme(float norme);
};

#endif
