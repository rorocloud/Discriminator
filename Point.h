#ifndef                                     POINT_H
# define                                    POINT_H

# include                                   <iostream>
# include                                   <string>
# include                                   <list>

class                                       Point
{
public:
  explicit                                Point();
  ~Point();

  struct                                  listPoint
  {
    float                               x;
    float                               y;
  };
  void                                    putInMyList(std::string);
  int                                     getNbCloud() const;

 private:
  int                                     nbCloud;
  std::list<struct listPoint>             myList;

};

#endif // POINT_H
