#ifndef PARSERBLOCK_H
#define PARSERBLOCK_H

#include <string>

using namespace std;

class ParserBlock
{
    public:
        virtual bool execute(string token)=0;
    protected:
    private:
};

#endif // PARSERBLOCK_H
