#include            "Discriminator.h"

int                 main(int argc, char **argv)
{
  try
    {
      if (argc >= 2)
	{
	  Discriminator    dis(argv[1]);
	  dis.openFile();
	}
      else
	  throw std::logic_error("Usage : ./Discriminator file");
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what() << std::endl;
      return (84);
    }
  return (0);
}
