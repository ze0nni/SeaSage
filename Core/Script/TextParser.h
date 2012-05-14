#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include "../ICore.h"
#include "ParserBlock.h"

#include <stdio.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>

#define PARSE_FLAG_END 0
#define PARSE_FLAG_WORD 1
#define PARSE_FLAG_DELIMITER 2

using namespace std;

class TextParser
{
    public:
        TextParser(ICore *__core, istream *__in);
        TextParser(ICore *__core, string s);
        virtual ~TextParser();

        void setDelimiter(char *s) {delimiter=s;};
        void parse(void* state, void (*proc)(void*, int, string));
        void parse(ParserBlock *block);
    protected:
    private:
        ICore *core;
        stringstream in;
        string delimiter;
};

#endif // TEXTPARSER_H
