#ifndef                 DISCRIMINATOR_H
#define                 DISCRIMINATOR_H

# include               <sstream>
# include               <fstream>
# include               <iostream>
# include               <stdexcept>
# include               <string>
# include               "Point.h"
# include		"Jarvis.h"

class                   Discriminator
{
public:
    explicit            Discriminator(char *);
                        ~Discriminator();

    std::string         intToString(int);
    int                 parseFile();
    int                 checkLine(std::string);
    void                openFile();

private:
    Point               *pointStruct;
    bool                checkPointStruct;
    std::string         name;
};

#endif // DISCRIMINATOR_H
