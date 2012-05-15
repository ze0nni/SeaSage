#ifndef PARSERBLOCK_H
#define PARSERBLOCK_H

#include <string>

#define PARSE_FLAG_END 0
#define PARSE_FLAG_TOKEN 1
#define PARSE_FLAG_DELIMITER 2
#define PARSE_FLAG_SPACE 3

using namespace std;

class ParserBlock
{
    public:
        ParserBlock(){child=0;};
        virtual bool execute(int flag, string token, int ln, int ch)=0;
        bool __execute(int flag, string token, int ln, int ch);
        void setChild(ParserBlock *__c) {child=__c;};
    protected:
    private:
        ParserBlock* child;
};

#endif // PARSERBLOCK_H
