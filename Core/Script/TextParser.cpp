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

void TextParser::parse(void* state, bool (*proc)(void*, int, string, int, int)) {
    int lineI;lineI=1;
    int charI;charI=1;

    char c;
    char lastChar;lastChar='\0';
    string buff;
    in.seekp(0);
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

bool blockParseProc(void* state, int flag, string token, int ln, int ch) {
    ParserBlock* block = (ParserBlock*)state;
    return block->__execute(flag, token, ln, ch);
}

void TextParser::parse(ParserBlock *block) {
    parse(block, &blockParseProc);
}

