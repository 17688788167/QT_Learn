#include "model.h"
#include <iostream>

Model::Model(QOpenGLFunctions_3_3_Core *glFun,const char *path)
{
    this->m_glFuns=glFun;
    loadModel(path);
    setupModelBox();
}

Model::~Model()
{
    for(int i=0;i<meshes.size();i++)
    {
        delete meshes[i];
    }
    meshes.empty();
}

void Model::Draw(QOpenGLShaderProgram &shader)
{
    for(unsigned int i =0;i<meshes.size();i++)
    {
        meshes[i]->Draw(shader);
    }
}

void Model::loadModel(string path)
{
    Assimp::Importer import;
    const aiScene*scene=import.ReadFile(path,aiProcess_Triangulate||aiProcess_FlipUVs);

    if(!scene||scene->mFlags&AI_SCENE_FLAGS_INCOMPLETE||!scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
        return;
    }
    directory=path.substr(0,path.find_last_of('/'));

    processNode(scene->mRootNode,scene);
}

void Model::processNode(aiNode *node, const aiScene *scene)
{
     // 处理节点所有的网格（如果有的话）
    for(unsigned int i=0;i<node->mNumMeshes;i++)
    {
        aiMesh* mesh=scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh,scene));
    }

    // 接下来对它的子节点重复这一过程
    for(unsigned int i=0;i<node->mNumChildren;i++)
    {
        processNode(node->mChildren[i],scene);
    }

}

Mesh* Model::processMesh(aiMesh *mesh, const aiScene *scene)
{
    vector<Vertex>vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;


    for(unsigned int i=0;i<mesh->mNumVertices;i++)
    {
        Vertex vertex;
        //处理顶点位置,法线纹理坐标
        QVector3D vector;

        //顶点位置
        vector.setX( mesh->mVertices[i].x);
        m_maxX=m_maxX<mesh->mVertices[i].x?mesh->mVertices[i].x:m_maxX;
        m_minX=m_minX>mesh->mVertices[i].x?mesh->mVertices[i].x:m_minX;
        vector.setY( mesh->mVertices[i].y);
        m_maxY=m_maxY<mesh->mVertices[i].y?mesh->mVertices[i].y:m_maxY;
        m_minY=m_minY>mesh->mVertices[i].y?mesh->mVertices[i].y:m_minY;
        vector.setZ( mesh->mVertices[i].z);
        m_maxZ=m_maxZ<mesh->mVertices[i].z?mesh->mVertices[i].z:m_maxZ;
        m_minZ=m_minZ>mesh->mVertices[i].z?mesh->mVertices[i].z:m_minZ;

        vertex.Position=vector;

        //法线
        vector.setX( mesh->mNormals[i].x);
        vector.setY( mesh->mNormals[i].y);
        vector.setZ( mesh->mNormals[i].z);

        vertex.Normal=vector;

        //纹理坐标
        if(mesh->mTextureCoords[0])
        {
            QVector2D vec;
            vec.setX(mesh->mTextureCoords[0][i].x);
            vec.setY(mesh->mTextureCoords[0][i].y);
            vertex.TexCoords=vec;
        }
        else
            vertex.TexCoords=QVector2D(0.0f,0.0f);


        vertices.push_back(vertex);
    }

    //处理索引
    for(unsigned i=0;i<mesh->mNumFaces;i++)
    {
        aiFace face=mesh->mFaces[i];

        for(unsigned int j=0;j<face.mNumIndices;j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    cout<<indices.size()<<"kkkkkk"<<endl;
    //处理材质
    if(mesh->mMaterialIndex>=0)
    {
        aiMaterial *material=scene->mMaterials[mesh->mMaterialIndex];

        vector<Texture> diffuseMaps=loadMaterialTexture(material,aiTextureType_DIFFUSE,"texture_diffuse");
        //在textures的末端插入diffuseMaps
        textures.insert(textures.end(),diffuseMaps.begin(),diffuseMaps.end());
        //textures.push_back(diffuseMaps);

        vector<Texture> specularMaps=loadMaterialTexture(material,aiTextureType_SPECULAR,"texture_specular");
        textures.insert(textures.end(),specularMaps.begin(),specularMaps.end());
    }
    //return Mesh();
    cout<<vertices.size()<<" "<<indices.size()<<" "<<textures.size()<<endl;


    return new Mesh(m_glFuns,vertices,indices,textures);
}

vector<Texture> Model::loadMaterialTexture(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i=0;i<mat->GetTextureCount(type);i++)
    {
        aiString str;
        mat->GetTexture(type,i,&str);
        bool skip=false;
        for(unsigned int j=0;j<textures_loaded.size();j++)
        {
            //strcmp(a,b)比较字符串的大小,如果返回值为0,说明a和b相等
            if(std::strcmp(textures_loaded[j].path.data(),str.C_Str())==0)
            {
                textures.push_back(textures_loaded[i]);
                skip=true;
                break;
            }
        }
        if(!skip)
        {
            Texture texture;
            texture.id=TextureFromFile(str.C_Str(),directory);

            texture.type=typeName;
            texture.path=str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}

unsigned int Model::TextureFromFile(const char *path, const string &directory)
{
    string filename=string(path);
    filename=directory+'/'+filename;

    QOpenGLTexture* texture=new QOpenGLTexture(QImage(filename.c_str()).mirrored());
    if(texture==NULL)
        cout<<"texture is null";
    else
        cout<<filename <<"  loaded"<<endl;

    return texture->textureId();
}

void Model::setupModelBox()
{

    modelBoxVertices.push_back(QVector3D(m_minX,m_minY,m_minZ));
    modelBoxVertices.push_back(QVector3D(m_minX,m_minY,m_maxZ));

    modelBoxVertices.push_back(QVector3D(m_minX,m_maxY,m_minZ));
    modelBoxVertices.push_back(QVector3D(m_minX,m_maxY,m_maxZ));

    modelBoxVertices.push_back(QVector3D(m_maxX,m_minY,m_minZ));
    modelBoxVertices.push_back(QVector3D(m_maxX,m_minY,m_maxZ));

    modelBoxVertices.push_back(QVector3D(m_maxX,m_maxY,m_minZ));
    modelBoxVertices.push_back(QVector3D(m_maxX,m_maxY,m_maxZ));

    m_indices.push_back(0);
    m_indices.push_back(1);

    m_indices.push_back(0);
    m_indices.push_back(2);

    m_indices.push_back(1);
    m_indices.push_back(3);

    m_indices.push_back(2);
    m_indices.push_back(3);


    m_indices.push_back(4);
    m_indices.push_back(5);

    m_indices.push_back(4);
    m_indices.push_back(6);

    m_indices.push_back(5);
    m_indices.push_back(7);

    m_indices.push_back(6);
    m_indices.push_back(7);

    m_indices.push_back(0);
    m_indices.push_back(4);

    m_indices.push_back(1);
    m_indices.push_back(5);

    m_indices.push_back(2);
    m_indices.push_back(6);

    m_indices.push_back(3);
    m_indices.push_back(7);

    m_glFuns->glGenVertexArrays(1,&m_boxGLData.VAO);
    m_glFuns->glGenBuffers(1, &m_boxGLData.VBO);
    m_glFuns->glGenBuffers(1,&m_boxGLData.EBO);

    m_glFuns->glBindVertexArray(m_boxGLData.VAO);
    m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, m_boxGLData.VBO);

    m_glFuns->glBufferData(GL_ARRAY_BUFFER,sizeof(QVector3D)*modelBoxVertices.size() ,&modelBoxVertices[0], GL_STATIC_DRAW);

    m_glFuns->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_boxGLData.EBO);

    m_glFuns->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*m_indices.size(),&m_indices[0],GL_STATIC_DRAW);

    m_glFuns->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QVector3D), (void*)0);
    m_glFuns->glEnableVertexAttribArray(0);

    m_glFuns->glBindVertexArray(0);


    //m_glFuns->gldraw

}

void Model::DrawBox(QOpenGLShaderProgram &shader)
{
    shader.setUniformValue("lightColor",QVector3D(1.0f,0.0f,0.0f));
    m_glFuns->glBindVertexArray(m_boxGLData.VAO);
    m_glFuns->glDrawElements(GL_LINES,m_indices.size(),GL_UNSIGNED_INT,0);
}

