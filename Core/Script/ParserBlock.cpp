#include "ParserBlock.h"

bool ParserBlock::__execute(int flag, string token, int ln, int ch) {
    if (child) {
        if (!child->execute(flag, token, ln, ch) || flag==PARSE_FLAG_END) {
            delete child;
            child = 0;
        }
        return true;
    } else {
        return execute(flag, token, ln, ch);
    }
}
