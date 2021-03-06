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
    //читаем начало, и пропускаем комментарий
    p->next('{'); p->seekToEndLine();
    do {
        string tk = p->readToken();
        if (tk=="Frame") {
            //Читаем дочерний фрейм
            if (!readFrameBlock(p, mesh)) return false;
        } else if (tk=="FrameTransformMatrix") {
            //Читаем матрицу трансформации
            Matrix4d m;
            if (!readMatrix(p, m)) return false;
            mesh->setTransformMatrix(m);
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

bool ModelX::readVector(TextParser *p, Vector3d &v) {
    float x = p->readFloat();
    float y = p->readFloat();
    float z = p->readFloat();
    p->seekToEndLine();
    v.set(x, y, z);
    return true;
}

bool ModelX::readMatrix(TextParser *p, Matrix4d &m) {
    //читаем начало, и пропускаем комментарий
    p->next('{'); p->seekToEndLine();
    //читаем значения
    for (int i=0; i<16; i++) {
        m.vector[i] = p->readFloat();
    }
    //закрываем
    p->next('}');
    return true;
}

bool ModelX::readMesh(TextParser *p, ModelMesh* mesh) {
    //читаем начало, и пропускаем комментарий
    p->next('{'); p->seekToEndLine();

    int vertexCount = p->readInt();
    Vector3d vertex[vertexCount];

    for(int i=0; i<vertexCount; i++) {
        if (!readVector(p, vertex[i])) return false;
    }

    int facesCount = p->readInt();
    for (int i=0; i<facesCount; i++) {
        int vc = p->readInt();//Число вершин
        int v[vc];//индексы вершин
        for(int vi=0; vi<vc; vi++)
            v[vi] = p->readInt();
        switch (vc) {
        case 3:
            mesh->rawAddVertex(vertex[v[0]]);
            mesh->rawAddVertex(vertex[v[1]]);
            mesh->rawAddVertex(vertex[v[2]]);
            break;
        case 4:
            mesh->rawAddVertex(vertex[v[0]]);
            mesh->rawAddVertex(vertex[v[1]]);
            mesh->rawAddVertex(vertex[v[2]]);
            mesh->rawAddVertex(vertex[v[0]]);
            mesh->rawAddVertex(vertex[v[2]]);
            mesh->rawAddVertex(vertex[v[3]]);
            break;
        default:
            getCore()->errlog("Wrong vertex count for face: %d", vc);
            return false;
        }
        p->seekToEndLine();
    }
    //читаем нормали
    do {
        string tk = p->readToken();
        if (tk=="MeshNormals") {
            if (!readNormals(p, mesh)) return false;
        } else if (tk.size()>1 && tk.substr(0,2)=="//") {
            //пропускаем строчный комментарий
            p->seekToEndLine();
        } else if (tk=="}") {
            return true;
        }
    } while(!p->eof());
    return true;
}

bool ModelX::readNormals(TextParser *p, ModelMesh* mesh) {
    //читаем начало, и пропускаем комментарий
    p->next('{'); p->seekToEndLine();
    int normalsCount = p->readInt();
    Vector3d normals[normalsCount];
    for(int i=0; i<normalsCount; i++) {
        if (!readVector(p, normals[i])) return false;
    }
    int facesCount = p->readInt();
    for (int i=0; i<facesCount; i++) {
        int nc = p->readInt();//Число вершин
        int n[nc];//индексы вершин
        for(int ni=0; ni<nc; ni++)
            n[ni] = p->readInt();
        switch (nc) {
        case 3:
            mesh->rawAddNormal(normals[n[0]]);
            mesh->rawAddNormal(normals[n[1]]);
            mesh->rawAddNormal(normals[n[2]]);
            break;
        case 4:
            mesh->rawAddNormal(normals[n[0]]);
            mesh->rawAddNormal(normals[n[1]]);
            mesh->rawAddNormal(normals[n[2]]);
            mesh->rawAddNormal(normals[n[0]]);
            mesh->rawAddNormal(normals[n[2]]);
            mesh->rawAddNormal(normals[n[3]]);
            break;
        default:
            getCore()->errlog("Wrong vertex count for face: %d", nc);
            return false;
        }
        p->seekToEndLine();
    }
}

bool ModelX::readMeshMaterialList(TextParser *p, ModelMesh* mesh) {
    //читаем начало, и пропускаем комментарий
    p->next('{'); p->seekToEndLine();

    //закрываем
    p->next('}');
    return true;
}
