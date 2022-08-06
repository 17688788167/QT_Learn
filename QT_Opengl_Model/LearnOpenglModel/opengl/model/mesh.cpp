#include "mesh.h"
#include "myopenglwidget.h"
Mesh::Mesh()
{
    
}

Mesh::~Mesh()
{

}

void Mesh::Draw(QOpenGLShaderProgram &shader, MyOpenglWidget* myopengl)
{

    switch (m_meshtype) {
    case EMeshType::Light:

        break;
    case EMeshType::Cube:


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
        break;
    }


//    QMatrix4x4 model;
//    QMatrix4x4 view;
//    QMatrix4x4 projection;
//    view=myopengl->m_camera.GetViewMatrix();
//    projection.perspective(myopengl->m_camera.Zoom,(float)myopengl->width()/myopengl->height(),0.1,1000);

//    shader.bind();
//    shader.setUniformValue("view",view);
//    shader.setUniformValue("projection",projection);
//    shader.setUniformValue("lightColor",QVector3D(0.4,0.8,0.3));
//    shader.setUniformValue("model", model);


    m_glFuns->glBindVertexArray(m_gldata.VAO);
    //m_glFuns->glDrawArrays(GL_TRIANGLES,0,36);
    m_glFuns->glDrawElements(GL_TRIANGLES,m_indices.size(),GL_UNSIGNED_INT,0);
}

Mesh::Mesh(QOpenGLFunctions_3_3_Core *glFun, vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures,EMeshType meshtype)
{
    this->m_glFuns=glFun;
    this->m_vertices=vertices;
    this->m_indices=indices;
    this->m_textures=textures;

    m_meshtype=meshtype;
//    QString vsPath;
//    QString fsPath;
//    switch (m_meshtype) {
//    case EMeshType::Light:
//        vsPath=":/shader/light.vert";
//        fsPath=":/shader/light.frag";
//        break;
//    case EMeshType::Cube:
//        vsPath=":/shader/object.vert";
//        fsPath=":/shader/object.frag";
//        break;
//    }

//    bool success;
//    success= m_shader.addShaderFromSourceFile(QOpenGLShader::Vertex,vsPath);
//    if(!success)
//         qDebug()<<"打开顶点着色器失败:"<<m_shader.log();
//    success= m_shader.addShaderFromSourceFile(QOpenGLShader::Fragment,fsPath);
//    if(!success)
//         qDebug()<<"打开片段着色器失败:"<<m_shader.log();

//     m_shader.link();

    setupMesh();

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

    m_glFuns->glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(unsigned int)*m_indices.size(),&m_indices[0],GL_STATIC_DRAW);

    m_glFuns->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    m_glFuns->glEnableVertexAttribArray(0);

    if(m_meshtype==EMeshType::Cube)
    {
        m_glFuns->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        m_glFuns->glEnableVertexAttribArray(1);

        m_glFuns->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        m_glFuns->glEnableVertexAttribArray(2);
    }

    m_glFuns->glBindVertexArray(0);



}
