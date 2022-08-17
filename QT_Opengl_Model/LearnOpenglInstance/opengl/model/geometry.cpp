#include "geometry.h"
#include "vertices.h"

void Geometry::Draw(QOpenGLShaderProgram &shader)
{
    shader.bind();
    shader.setUniformValue("pointColor",QVector3D(0.0f,1.0f,0.0f));
    m_glFuns->glBindVertexArray(m_gldata.VAO);

    m_glFuns->glDrawArrays(GL_POINTS, 0, 4);
}

void Geometry::setupMesh()
{
    m_glFuns->glEnable((GL_PROGRAM_POINT_SIZE));
    //创建VBO，VAO，EBO对象,并赋予id
    m_glFuns->glGenVertexArrays(1,&m_gldata.VAO);
    m_glFuns->glGenBuffers(1, &m_gldata.VBO);

    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, m_gldata.VBO);

    m_glFuns->glBufferData(GL_ARRAY_BUFFER,sizeof(points),NULL, GL_STATIC_DRAW);


//        void *ptr=m_glFuns->glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
//        std::memcpy(ptr,&Data::vertices[0],sizeof(Data::vertices)/2 );
//      //qDebug()<<ptr<<"  sssssss";
//        std::memcpy((int*)ptr+sizeof(Data::vertices)/8,&Data::vertices[sizeof(Data::vertices)/2/sizeof(float)],sizeof(Data::vertices)/2 );
//        m_glFuns->glUnmapBuffer(GL_ARRAY_BUFFER);

    m_glFuns->glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(points),&points[0]);
    //m_glFuns->glBufferSubData(GL_ARRAY_BUFFER,sizeof(Data::vertices)/2,sizeof(Data::vertices)/2,&Data::vertices[sizeof(Data::vertices)/2/sizeof(float)]);

    m_glFuns->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
     m_glFuns->glEnableVertexAttribArray(0);
    m_glFuns->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(sizeof(float)*2));
    m_glFuns->glEnableVertexAttribArray(1);

    m_glFuns->glBindVertexArray(0);
}
