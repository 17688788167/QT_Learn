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

};

#endif // MODEL_H
