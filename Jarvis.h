#ifndef JARVIS_H_
# define JARVIS_H_

#include "Vector2.h"
#include "Point.h"
#include <vector>
#include <cmath>
#include <iostream>

#define INIT	(0)

class	Jarvis
{
 public:
  Jarvis();
  ~Jarvis();
  bool				processus(std::list<Point::listPoint> &list);
  // GETTER
  int				getNbCld() const;
  std::list<Point::listPoint>	getList() const;
  float				getMoyN() const;
  Point::listPoint		getA() const;
  Point::listPoint		getM() const;
  Point::listPoint		getB() const;
  float				getAlpha() const;
  // SETTER
  void				setNbCld(int nbCld);
  void				setList(std::list<Point::listPoint> &lp);
  void				setMoyN(float moyN);
  void				setA(Point::listPoint &a);
  void				setM(Point::listPoint &m);
  void				setB(Point::listPoint &b);
  void				setAlpha(float alpha);
  // CALC
  void				calc_newM();
  void				calc_moyN();
  float				calc_vectorNorme(Point::listPoint &a, Point::listPoint &b);
  float				calc_angle(Point::listPoint &b, Point::listPoint &a, Point::listPoint &m);
  // FIND
  void				find_start();
  void				find_b();
  // TRANSFORMATION
  Point::listPoint		rotation(float angle) const;

 private:
  int				nbCld_;
  std::list<Point::listPoint>	pList_;
  float				moyN_;
  Point::listPoint		a_;
  Point::listPoint		m_;
  Point::listPoint		b_;
  float				alpha_;
};

#endif
