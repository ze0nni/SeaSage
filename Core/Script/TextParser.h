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
        /**
        конструктор принимает буфер
        */
        TextParser(ICore *__core, istream *__in);
        /**
        конструктор принимает строку символов
        */
        TextParser(ICore *__core, string s);
        // todo:~TextParser()
        virtual ~TextParser();

        //void setDelimiter(char *s) {delimiter=s;};
        //void setSpaces(char *s) {spaces=s;};
        /**
        помещает текущую позицию в стек
        */
        void push();
        /**
        извлекает из стека позицию и перемещается на нее
        */
        void ret();
        /**
        извлекает позицию из стека, не производя переход
        */
        void pop();
        /**
        извлекает из стека позицию и перемещается на нее
        возвращает строку из из промежутка текущей позиции и позиции в которую вернется
        */
        string retString();
        /**
        извлекает позицию из стека и возврощает строку между этой позицией и текущей позицией
        не производит переход
        */
        string popString();
        /**
        Возвращает следующий символ
        */
        char next();
        /**
        останавливается перед символом __c
        */
        bool next(char __c);
        /**
        останавливается перед первым символом, отличным от __c
        */
        bool nextn(char __c);
        /**
        останавливается перед одним из символов в строке __c
        */
        bool next(char* __c);
        /**
        останавливается перед первым символом, не содержащимся в строке __c
        */
        bool nextn(char* __c);
        /**
        ищет пока процедура proc не вернет true
        */
        bool nextp(bool proc(const char));
        /**
        возвращает следующий символ, не сдвигая позицию
        */
        char peek();
        /**
        оснатавливается перед первым пробелом, переносом строки или табуляцией
        */
        bool seekToSpacesBegin(){return nextp(&seekToSpacesBeginProc);};
        /**
        пропускает все пробелы, переносы строк и табуляции
        */
        bool seekToSpacesEnd(){return nextp(&seekToSpacesEndProc);};
        /**
        пропускает строку до символа переноса
        */
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
