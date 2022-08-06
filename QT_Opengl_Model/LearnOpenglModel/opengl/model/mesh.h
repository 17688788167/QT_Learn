#ifndef MESH_H
#define MESH_H

#include <QOpenGLShaderProgram>
using namespace std;


class Mesh
{





public:
    Mesh();
    ~Mesh();

    void Draw(QOpenGLShaderProgram &shader);

};

#endif // MESH_H
