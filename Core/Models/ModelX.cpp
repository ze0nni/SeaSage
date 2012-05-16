#include "ModelX.h"

ModelX::ModelX(ICore *__core):Model(__core)
{
    //ctor
}

ModelX::~ModelX()
{
    //dtor
}

bool ModelX::load(istream *in) {
    FileXHead header;
    in->read((char*)&header, sizeof(header));
    header.signatureSpace='\0';
    header.formatSpace='\0';
    header.floatSizeSpace='\0';
    //проверка сигнатуры
    if (strcmp(header.signature, "xof")) {
        getCore()->errlog("Wrong file signature %s", header.signature);
        return false;
    }
    //чтение txt
    if (!strcmp(header.format, "txt")) {

        return loadTxt(in);
    }
    getCore()->errlog("Wrong file format %s", header.format);
    return false;
}

bool ModelX::loadTxt(istream *in) {
    TextParser parser(0, in);

}
