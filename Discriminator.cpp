#include    "Discriminator.h"

Discriminator::Discriminator(char *fileName)
{
  name = fileName;
  checkPointStruct = false;
}

Discriminator::~Discriminator()
{
  if (checkPointStruct)
    delete pointStruct;
}

int             Discriminator::checkLine(std::string textFile)
{
  bool        vir = false;
  int         nbVir;
  int         check;

  check = -2;
  nbVir = -1;
  for (int i = 0; textFile[i] != '\0'; i++)
    {
      if ((textFile[i] >= '0' && textFile[i] <= '9') && vir == false)
	check = -1;
      else if ((textFile[i] >= '0' && textFile[i] <= '9') && vir == true)
	check = 0;
      else if (textFile[i] == ';')
        {
            vir = true;
            nbVir++;
        }
    }
  if (nbVir > 0)
    vir = false;
  else if (check == 0 && vir == true)
    return 0;
  throw std::logic_error("Syntax non conforme");
  return 84;
}

int             Discriminator::parseFile()
{
  std::ifstream file(name.c_str(), std::ios::in);
  if (file)
    {
      std::string  line;
      bool    empty = true;
      while (getline(file, line))
        {
	  if (empty)
	    {
	      empty = false;
	      pointStruct = new Point;
	      checkPointStruct = true;
	    }
	  if (checkLine(line))
	    return 84;
	  pointStruct->putInMyList(line);
        }
      file.close();
      if (empty)
        {
	  throw std::logic_error("Fichier vide");
	  return 84;
        }
      return 0;
    }
  throw std::logic_error("Ce fichier ne peut pas etre lu");
  return 84;
}

void            Discriminator::openFile()
{
  if (parseFile())
    return ;
  std::cout << pointStruct->getNbCloud() << std::endl;
}

std::string     Discriminator::intToString(int nb)
{
  std::ostringstream  oss;

  oss << nb;
  return oss.str();
}
