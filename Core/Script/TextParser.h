#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include "../ICore.h"
#include "ParserBlock.h"

#include <stdio.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <sstream>
#include <stack>

using namespace std;

class TextParser
{
    public:
        TextParser(ICore *__core, istream *__in);
        TextParser(ICore *__core, string s);
        // todo:~TextParser()
        virtual ~TextParser();

        //void setDelimiter(char *s) {delimiter=s;};
        //void setSpaces(char *s) {spaces=s;};

        void push();
        void ret();
        void pop();
        string retString();
        string popString();
        char next();
        bool next(char __c);
        bool next(char* __c);
        bool nextp(bool proc(const char));
        char peek();

        bool seekToSpacesBegin(){return nextp(&seekToSpacesBeginProc);};
        bool seekToSpacesEnd(){return nextp(&seekToSpacesEndProc);};
        bool seekToEndLine(){return nextp(&seekToEndLineProc);};
    protected:
        static bool seekToSpacesBeginProc(const char c){return strchr(" \r\n\t", c);};
        static bool seekToSpacesEndProc(const char c){return !strchr(" \r\n\t", c);};
        static bool seekToEndLineProc(const char c){return !strchr("\r\n", c);};
    private:
        ICore *core;
        stringstream in;
        stack<int> position;
        //string delimiter;
        //string spaces;
};

#endif // TEXTPARSER_H
