#include "light.h"



//Light::Light(QOpenGLFunctions_3_3_Core *glfun,const QVector3D& light)
//{
//    m_glFuns=glfun;
//    m_lightColor=light;
//    setupMesh();
//}

//void Light::Draw(QOpenGLShaderProgram &shader)
//{
//    shader.setUniformValue("lightColor",m_lightColor);
//    m_glFuns->glBindVertexArray(m_gldata.VAO);
//    m_glFuns->glDrawElements(GL_TRIANGLES,36,GL_UNSIGNED_INT,0);
//}

//void Light::setupMesh()
//{
//    //创建VBO，VAO，EBO对象,并赋予id
//    m_glFuns->glGenVertexArrays(1,&m_gldata.VAO);
//    m_glFuns->glGenBuffers(1, &m_gldata.VBO);

//    m_glFuns->glBindVertexArray(m_gldata.VAO);
//    m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, m_gldata.VBO);

//    m_glFuns->glBufferData(GL_ARRAY_BUFFER,sizeof(Data::vertices),Data::vertices, GL_STATIC_DRAW);

//    m_glFuns->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
//    m_glFuns->glEnableVertexAttribArray(0);

//    m_glFuns->glBindVertexArray(0);
//}
