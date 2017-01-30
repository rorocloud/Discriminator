#include "Jarvis.h"


Jarvis::Jarvis()
{
  nbCld_ = INIT;
  moyN_ = INIT;
  alpha_ = INIT;
}

Jarvis::~Jarvis()
{

}

bool				Jarvis::processus(std::list<Point::listPoint> &list)
{
  pList_ = list;
  std::vector<Point::listPoint>	n1;

 // PRINT points
  std::cout << "--------------------------\nStart test on 'pList'\n--------------------------\n\n";
  for (std::list<Point::listPoint>::iterator ppt = pList_.begin(); ppt != pList_.end(); ppt++)
    std::cout << ppt->x << "X\t" << ppt->y << "Y\n";
  //
  
  find_start();
  // PRINT a_
  std::cout << "--------------------------\nStart test on 'find_start()'\n--------------------------\n\n";
  std::cout << a_.x << "x\t" << a_.y << "Y\n";
  //
  n1.push_back(a_);
  
  calc_moyN();
  // PRINT moyN
  std::cout << "--------------------------\nStart test on 'calc_moyN()'\n--------------------------\n\n";
  std::cout << moyN_ << "\n";
  //

  for (int i = 0; i < 10; i++)
    {
      calc_newM();
      // PRINT m_
      std::cout << "--------------------------\nStart test on 'calc_newM()'\n--------------------------\n\n";
      std::cout << m_.x << "x\t" << m_.y << "Y\n";
      //

      find_b();
      // PRINT b_
      std::cout << "--------------------------\nStart test on 'find_b()'\n--------------------------\n\n";
      std::cout << b_.x << "x\t" << b_.y << "Y\n";
      //
      n1.push_back(b_);
      a_ = b_;
    }
  return true;
}

// GETTER
int				Jarvis::getNbCld() const
{
  return nbCld_;
}

std::list<Point::listPoint>	Jarvis::getList() const
{
  return pList_;
}

float				Jarvis::getMoyN() const
{
  return moyN_;
}

Point::listPoint		Jarvis::getA() const
{
  return a_;
}

Point::listPoint		Jarvis::getM() const
{
  return m_;
}

Point::listPoint		Jarvis::getB() const
{
  return b_;
}

float				Jarvis::getAlpha() const
{
  return alpha_;
}

// SETTER
void				Jarvis::setNbCld(int nbCld)
{
  nbCld_ = nbCld;
}

void				Jarvis::setList(std::list<Point::listPoint> &lp)
{
  pList_ = lp;
}

void				Jarvis::setMoyN(float moyN)
{
  moyN_ = moyN;
}

void				Jarvis::setA(Point::listPoint &a)
{
  a_ = a;
}

void				Jarvis::setM(Point::listPoint &m)
{
  m_ = m;
}

void				Jarvis::setB(Point::listPoint &b)
{
  b_ = b;
}

void				Jarvis::setAlpha(float alpha)
{
  alpha_ = alpha;
}

// CALC
void				Jarvis::calc_newM()
{
  if (alpha_ == INIT)
    {
      m_.x = a_.x;
      m_.y = a_.y + moyN_;
    }
  else
    {
      m_.x = a_.x;
      m_.y = a_.y + moyN_;
      m_ = rotation(alpha_);
    }
}

void Jarvis::calc_moyN()
{
  std::list<Point::listPoint>::iterator sp = pList_.begin(), ip = sp;
  float				tmp = 0;
  int				i = 1, j = 0, len = 0;
  ip++;

  while (sp != pList_.end())
    {
      while (ip != pList_.end())
	{
	  tmp += calc_vectorNorme(*sp, *ip);
	  ip++;
	  len++;
	}
      i++;
      ip = pList_.begin();
      j = 0;
      while (j < i)
	{
	  ip++;
	  j++;
	}
      sp++;
    }
  moyN_ = tmp / len;
}

float				Jarvis::calc_vectorNorme(Point::listPoint &a, Point::listPoint &b)
{
  return (std::sqrt((std::abs(pow(b.x - a.x, 2)) + std::abs(pow(b.y - a.y, 2)))));
}

float				Jarvis::calc_angle(Point::listPoint &b, Point::listPoint &a, Point::listPoint &m)
{
  float am, ab, bm, angle, num, den;

  am = calc_vectorNorme(m, a);
  ab = calc_vectorNorme(b, a);
  bm = calc_vectorNorme(m, b);

  num = (pow(am, 2) + pow(ab, 2) + pow(bm, 2));
  den = (2 * am * ab);
  num = (num / den);
  angle = std::cosh(num);
  return angle;
}

// FIND
void				Jarvis::find_start()
{
  float				minY;
  for (std::list<Point::listPoint>::iterator il0 = pList_.begin(), il1 = pList_.begin(); il1 != pList_.end(); il1++)
    {
      if (il0 == pList_.begin())
	{
	  if ((minY = std::min(il0->x, il1->x)) == il0->x)
	    {
	      a_.x = il0->x;
	      a_.y = il0->y;
	    }
	  else
	    {
	      a_.x = il1->x;
	      a_.y = il1->y;
	    }
	  il0++;
	}
      else
	if ((minY = std::min(minY, il1->x)) == il1->x)
	  {
	    a_.x = il1->x;
	    a_.y = il1->y;
	  }
    }
}

void				Jarvis::find_b()
{
  float				tmp, tmp0, tmp1, minA;
  std::vector<Point::listPoint>	lp;

  // Récupère la liste de point dans le cercle de centre 'a_' et de rayon 'moyN'
  for (std::list<Point::listPoint>::iterator ip = pList_.begin(); ip != pList_.end(); ip++)
    if ((calc_vectorNorme(a_, *ip)) < moyN_)
      {
	if ((tmp = (calc_angle(*ip, a_, m_))) > 0 && tmp < 180)
	  {
	    lp.push_back(*ip);
	  }
      }
  if (lp.size() > 0 && lp.size() < pList_.size())
    {
      // Récupère le point pour lequel l'angle est le plus petit
      for (std::vector<Point::listPoint>::iterator is0 = lp.begin(), is1 = is0 + 1; is1 != lp.end(); is1++)
	{
	  tmp0 = calc_angle(*is0, a_, m_);
	  tmp1 = calc_angle(*is1, a_, m_);
	  if ((minA = (std::min(tmp0, tmp1))) == tmp0)
	    b_ = *is0;
	  else
	    b_ = *is1;
	  is0++;
	}
      alpha_ = minA;
    }
}

// TRANSFORMATION
Point::listPoint		Jarvis::rotation(float angle) const
{
  Point::listPoint		newPt;

  newPt.x = m_.x * std::cos(angle) - m_.y * std::sin(angle);
  newPt.y = m_.x * std::sin(angle) + m_.y * std::cos(angle);
  return newPt;
}
