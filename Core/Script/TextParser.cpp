#include "TextParser.h"

TextParser::TextParser(ICore *__core, istream *__in) {
    core = __core;
    string line;
    while (std::getline(*__in, line)) {
        in << line << endl;
    }
    in << '\0';
    in.seekp(0);
}

TextParser::TextParser(ICore *__core, string __s) {
    core = __core;
    in << __s;
    in << '\0';
    in.seekg(0);
}

TextParser::~TextParser()
{
    //dtor
}

void TextParser::push(){
    position.push(in.tellg());
}

void TextParser::ret(){
    in.seekg(position.top());
    position.pop();
}

void TextParser::pop(){
    position.pop();
}

string TextParser::retString(){
    int ret = position.top();
    string res = popString();
    in.seekg(ret);
    return res;
}

string TextParser::popString(){
    int ss = position.top(); //string start
    position.pop();
    int se = in.tellg(); //string end

    char buff[se-ss];
    in.seekg(ss);
    in.read(buff, sizeof(buff));

    return string (buff, se-ss);
}

char TextParser::next() {
    char c;
    in.get(c);
    return c;
}

bool TextParser::next(const char __c) {
    char c;
    while (in.get(c)) {
        if (in.peek()==__c) return true;
    }
    return false;
}

bool TextParser::nextn(const char __c) {
    char c;
    while (in.get(c)) {
        if (in.peek()!=__c) return true;
    }
    return false;
}

bool TextParser::next(const char* __s) {
    char c;
    while (in.get(c)) {
        if (strchr(__s, in.peek())) return true;
    }
    return false;
}

bool TextParser::nextn(const char* __s) {
    char c;
    while (in.get(c)) {
        if (!strchr(__s, in.peek())) return true;
    }
    return false;
}

bool TextParser::nextp(bool proc(const char)) {
    char c;
    while (in.get(c)) {
        if (proc(in.peek())) return true;
    }
    return false;
}

char TextParser::peek() {
    return in.peek();
}

string TextParser::readRawString(const char q) {
}

string TextParser::readEscString(const char q) {

}

string TextParser::readRawString() {

}

string TextParser::readEscString() {
}

/*
void TextParser::parse(void* state, bool (*proc)(void*, int, string, int, int)) {
    int lineI;lineI=1;
    int charI;charI=1;

    char c;
    char lastChar;lastChar='\0';
    string buff;
    in.seekg(0);
    while (true) {
        if (!in.get(c)) {
            if (buff.size()!=0)
                proc(state, PARSE_FLAG_TOKEN, buff, lineI, charI);
            proc(state, PARSE_FLAG_END, "", lineI, charI);
            return;
        }
        if (c=='\n') {
            lineI++;
            charI=0;
        } else {
            charI++;
        }
        //если пробел
        if (strchr(spaces.c_str(), c)) {
            if (!strchr(spaces.c_str(), lastChar) && buff.size()!=0) {
                if (!proc(state, PARSE_FLAG_TOKEN, buff, lineI, charI)) return;
                buff.clear();
            }
            buff.push_back(c);
            if (!strchr(spaces.c_str(), in.peek())) {
                if (!proc(state, PARSE_FLAG_SPACE, buff, lineI, charI)) return;
                buff.clear();
            }
            //continue;
        } else
        //если разделительный символ
        if (strchr(delimiter.c_str(), c)) {
            if (buff.size()!=0)
                if (!proc(state, PARSE_FLAG_TOKEN, buff, lineI, charI)) return;
            buff.clear();
            string dc; dc=c;
            if (!proc(state, PARSE_FLAG_DELIMITER, dc, lineI, charI)) return;
            //continue;
        } else
        //все остальные символы
        {
            buff.push_back(c);
        }
        lastChar = c;
    }
}
*/

/*
bool blockParseProc(void* state, int flag, string token, int ln, int ch) {
    ParserBlock* block = (ParserBlock*)state;
    return block->__execute(flag, token, ln, ch);
}
*/

/*
void TextParser::parse(ParserBlock *block) {
    parse(block, &blockParseProc);
}
*/

