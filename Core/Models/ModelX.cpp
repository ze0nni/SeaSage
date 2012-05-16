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
    do {
        string tk;
        tk = parser.readToken();
        if (tk=="Frame") {
            if (!readFrameBlock(&parser, 0)) return false;
        } else if (tk=="}") {
            return true;
        } else if (tk.size()>1 && tk.substr(0,2)=="//") {
            todo: parser.seekToEndLine();
        } else {
            getCore()->errlog("Wrong token <%s>", tk.c_str());
            return false;
        }
    } while(!parser.eof());
    return true;
}

bool ModelX::readFrameBlock(TextParser *p, ModelMesh *parent) {
    //читаем имя фрейма
    string  TkName = p->readToken();
    //создаем новый фрейм
    //или выбираем корневой фрейм
    ModelMesh *mesh;
    if (parent) {
        mesh = new ModelMesh();
        parent->addChild(TkName, mesh);
    } else {
        mesh =getRootMesh();
    }
    //перемещаемся к открывающейся скобке
    p->next('{');
    do {
        string tk = p->readToken();
        if (tk=="Frame") {
            //Читаем дочерний фрейм
            if (!readFrameBlock(p, mesh)) return false;
        } else if (tk=="FrameTransformMatrix") {
            //Читаем матрицу трансформации
            Matrix4d m;
            if (!readMatrix(p, m)) return false;
            //todo: set transform matrix
        } else if (tk=="Mesh") {
            //Читаем матрицу трансформации
            if (!readMesh(p, mesh)) return false;
        } else if (tk=="MeshMaterialList") {
            //читаем материалы
            if (!readMeshMaterialList(p, mesh)) return false;
        } else if (tk=="}") {
            return true;
        } else if (tk.size()>1 && tk.substr(0,2)=="//") {
            //пропускаем строчный комментарий
            p->seekToEndLine();
        } else {
            getCore()->errlog("Wrong token <%s>", tk.c_str());
            return false;
        }
    } while(!p->eof());
    //
    return true;
}

bool ModelX::readMatrix(TextParser *p, Matrix4d &m) {
    //читаем начало
    p->next('{');
    //читаем значения
    for (int i=0; i<16; i++) {
        m.vector[i] = p->readFloat();
    }
    //закрываем
    p->next('}');
    return true;
}

bool ModelX::readMesh(TextParser *p, ModelMesh* mesh) {
    //читаем начало
    p->next('{');

    //закрываем
    p->next('}');
    return true;
}

bool ModelX::readMeshMaterialList(TextParser *p, ModelMesh* mesh) {
    //читаем начало
    p->next('{');

    //закрываем
    p->next('}');
    return true;
}
