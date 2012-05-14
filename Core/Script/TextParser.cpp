#include "TextParser.h"

TextParser::TextParser(ICore *__core, istream *__in) {
    core = __core;
    string line;
    while (std::getline(*__in, line)) {
        in << line << endl;
    }
}

TextParser::TextParser(ICore *__core, string __s) {
    core = __core;
    in << __s;
}

TextParser::~TextParser()
{
    //dtor
}

void TextParser::parse(void* state, void (*proc)(void*, int, string)) {
    char c;
    string buff;
    in.seekp(0);
    while (true) {
        if (!in.get(c)) {
            if (buff.size()!=0)
                proc(state, PARSE_FLAG_WORD, buff);
            proc(state, PARSE_FLAG_END, "");
            return;
        }
        if (strchr(delimiter.c_str(), c)) {
            if (buff.size()!=0)
                proc(state, PARSE_FLAG_WORD, buff);
            buff.clear();
            string dc; dc=c;
            proc(state, PARSE_FLAG_DELIMITER, dc);
            continue;
        }
        buff.push_back(c);
    }
}

void TextParser::parse(ParserBlock *block) {
    //todo:
}

