#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include "../ICore.h"
#include "ParserBlock.h"

#include <stdio.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

class TextParser
{
    public:
        TextParser(ICore *__core, istream *__in);
        TextParser(ICore *__core, string s);
        // todo:~TextParser()
        virtual ~TextParser();

        void setDelimiter(char *s) {delimiter=s;};
        void setSpaces(char *s) {spaces=s;};
        void parse(void* state, bool (*proc)(void*, int, string, int, int));
        void parse(ParserBlock *block);
    protected:
    private:
        ICore *core;
        stringstream in;
        string delimiter;
        string spaces;
};

#endif // TEXTPARSER_H
