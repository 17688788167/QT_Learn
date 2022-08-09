#ifndef MODEL_H
#define MODEL_H

#include<QOpenGLTexture>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "mesh.h"

using namespace std;
class Model
{
public:

Model(QOpenGLFunctions_3_3_Core* glFun,const char *path);

~Model();

void Draw(QOpenGLShaderProgram &shader);

private:
QOpenGLFunctions_3_3_Core *m_glFuns;


vector<Mesh*>meshes;

//目录
string directory;

void loadModel(string path);
void processNode(aiNode *node,const aiScene *scene);


Mesh* processMesh(aiMesh *mesh,const aiScene *scene);

vector<Texture> loadMaterialTexture(aiMaterial* mat,aiTextureType type,string typeName);
 unsigned int TextureFromFile(const char *path, const string &directory);

 vector<Texture> textures_loaded;

 float m_maxX=-10000.0f;
 float m_maxY=-10000.0f;
 float m_maxZ=-10000.0f;

 float m_minX=10000.0f;
 float m_minY=10000.0f;
 float m_minZ=10000.0f;

public:
 inline float getModelWidth()const
 {
     return m_maxX-m_minX;
 }

 inline float getModelHeight()const
 {
     return m_maxY-m_minY;
 }

  FGLData m_boxGLData;

 vector<QVector3D> modelBoxVertices;
 vector <unsigned int> m_indices;

 void setupModelBox();
 void DrawBox(QOpenGLShaderProgram& shader);
};

#endif // MODEL_H
