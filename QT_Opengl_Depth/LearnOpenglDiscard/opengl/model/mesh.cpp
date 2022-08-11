#include "mesh.h"
#include <iostream>

Mesh::~Mesh()
{

}

void Mesh::Draw(QOpenGLShaderProgram &shader)
{
    //绑定贴图
    unsigned int diffuseNr=1;
    unsigned int specularNr=1;
    for(unsigned int i=0;i<m_textures.size();++i)
    {
        m_glFuns->glActiveTexture(GL_TEXTURE0+i);
        string number;
        string name=m_textures[i].type;


        if(name=="texture_diffuse")
            number=std::to_string(diffuseNr++);
        else if(name=="texture_specular")
            number=std::to_string(specularNr++);

        shader.setUniformValue(("material."+name+number).c_str(),i);
        m_glFuns->glBindTexture(GL_TEXTURE_2D,m_textures[i].id);
    }
    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glDrawElements(GL_TRIANGLES,m_indices.size(),GL_UNSIGNED_INT,0);
}

Mesh::Mesh(QOpenGLFunctions_3_3_Core *glFun, vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
{

    this->m_glFuns=glFun;
    this->m_vertices=vertices;
    this->m_indices=indices;
    this->m_textures=textures;
    setupMesh();
}

Mesh::Mesh(const Mesh &mesh)
{

}

void Mesh::setupMesh()
{
    //创建VBO，VAO，EBO对象,并赋予id
    m_glFuns->glGenVertexArrays(1,&m_gldata.VAO);
    m_glFuns->glGenBuffers(1, &m_gldata.VBO);
    m_glFuns->glGenBuffers(1,&m_gldata.EBO);


    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, m_gldata.VBO);

    m_glFuns->glBufferData(GL_ARRAY_BUFFER,sizeof(Vertex)*m_vertices.size() ,&m_vertices[0], GL_STATIC_DRAW);

    m_glFuns->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_gldata.EBO);

    cout<<m_indices.size()<<"sada"<<endl;

    m_glFuns->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*m_indices.size(),&m_indices[0],GL_STATIC_DRAW);

    m_glFuns->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    m_glFuns->glEnableVertexAttribArray(0);

        m_glFuns->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        m_glFuns->glEnableVertexAttribArray(1);

        m_glFuns->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        m_glFuns->glEnableVertexAttribArray(2);


    m_glFuns->glBindVertexArray(0);
}
