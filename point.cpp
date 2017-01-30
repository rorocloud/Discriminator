#include "Point.h"

Point::Point()
{
  nbCloud = 0;
}

Point::~Point()
{
}

void        Point::putInMyList(std::string textFile)
{
    std::string nbX = "";
    std::string nbY = "";
    bool        vir = false;

    for (int i = 0; textFile[i] != '\0'; i++)
    {
        if (textFile[i] == ';')
            vir = true;
        else if (!vir)
            nbX += textFile[i];
        else if (vir)
            nbY += textFile[i];
    }

    struct listPoint    elemList;

    elemList.x = std::stof(nbX);
    elemList.y = std::stof(nbY);
    myList.push_back(elemList);
}

int     Point::getNbCloud() const
{
  return nbCloud;
}
