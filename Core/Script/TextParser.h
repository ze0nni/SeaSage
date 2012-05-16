#ifndef TEXTPARSER_H
#define TEXTPARSER_H

#include "../ICore.h"

#include <stdio.h>
#include <stdlib.h>
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
        возвращает true если достигнут конец
        */
        bool eof() {
            return !in.good();
        }
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
        bool next(const char __c);
        /**
        останавливается перед первым символом, отличным от __c
        */
        bool nextn(const char __c);
        /**
        останавливается перед одним из символов в строке __c
        */
        bool next(const char* __c);
        /**
        останавливается перед первым символом, не содержащимся в строке __c
        */
        bool nextn(const char* __c);
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
        // utils
        /**
        пропускает все пробелы, символы табуляции и переноса, и возвращает набор символов,
        отделенный следующей группой разделителей
        */
        string readToken() {
            seekToSpacesEnd();
            push();
            seekToSpacesBegin();
            return popString();
        }
        /**
        пропускает все пробелы, символы табуляции и переноса
        и возвращает группу идущих подряд символов из строки __c
        например
            для строки "320x200"
            cout << readTokenOfChar("0123456789");// 320
        */
        string readTokenOfChar(const char *__c) {
            seekToSpacesEnd();
            push();
            nextn(__c);
            return popString();
        }
        /**
        возвращает целое число
        */
        int readInt() {
            return atoi(readTokenOfChar("-0123456789").c_str());
        }
        /**
        возвращает вещественное число
        */
        float readFloat() {
            return atof(readTokenOfChar("-.0123456789").c_str());
        }
        /**
        Возвращает строку заключенную между символами q
        под q могут быть символы любые одиночные символы
        либо парные открывающаяся парная скобка
            <([{«
        */
        string readRawString(const char q);
        /**
        Возвращает строку заключенную между символами q
        строка может содержать экранируемые символы
            \n\r\\\"
        которые будут учитываться
        */
        string readEscString(const char q);
        /**
        Возвращает строку заключенную между символами на которых сейчас стоит курсор
        */
        string readRawString();
        /**
        Возвращает строку заключенную между символами на которых сейчас стоит курсор
        в строке могут находиться экранируемые символы
        */
        string readEscString();
    protected:
        static bool seekToSpacesBeginProc(const char c){return strchr(" \r\n\t", c);};
        static bool seekToSpacesEndProc(const char c){return !strchr(" \r\n\t", c);};
        static bool seekToEndLineProc(const char c){return strchr("\r\n", c);};
    private:
        ICore *core;
        stringstream in;
        stack<int> position;
        //string delimiter;
        //string spaces;
};

#endif // TEXTPARSER_H
