#ifndef MESH_H
#define MESH_H

#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_3_3_Core>
#include <string>
#include <vector>
#include <data.h>
#include "camera.h"


using namespace std;

class MyOpenglWidget;
enum EMeshType
{
    Light,
    Cube
};


struct Vertex
{
    QVector3D Position;
    QVector3D Normal;
    QVector2D TexCoords;
};

struct Texture
{
    unsigned int id;
    string type;
    string path;
};

class Mesh
{

public:
    vector<Vertex> m_vertices;
    vector <unsigned int> m_indices;
    vector <Texture> m_textures;

    QOpenGLShaderProgram m_shader;

    FGLData m_gldata;
    //EMeshType m_meshtype;

public:
    ~Mesh();

    void Draw(QOpenGLShaderProgram &shader);

    void DrawInstance(QOpenGLShaderProgram &shader,unsigned int amount);
    //Mesh(QOpenGLFunctions_3_3_Core *glFun,vector<Vertex>vertices,vector<unsigned int>indices,vector<Texture>textures,EMeshType meshtype);
    Mesh(QOpenGLFunctions_3_3_Core *glFun, vector<Vertex> vertices,
         vector<unsigned int> indices, vector<Texture> textures);
    Mesh(const Mesh & mesh);

private:


    QOpenGLFunctions_3_3_Core * m_glFuns;

    void setupMesh();

};

#endif // MESH_H
