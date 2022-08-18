#include "screen.h"
#include "data.h"


void Screen::Draw(QOpenGLShaderProgram &shader)
{
    shader.bind();
    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glDrawArraysInstanced(GL_TRIANGLES, 0, 6,100);
}

void Screen::setupMesh()
{

    QVector2D translations[100];
    int index = 0;
    float offset = 0.1f;
    for(int y = -10; y < 10; y += 2) {
        for(int x = -10; x < 10; x += 2) {
            QVector2D translation;
            translation.setX((float)x / 10.0f + offset);
            translation.setY((float)y / 10.0f + offset);
            translations[index++] = translation;
        }
    }

      m_glFuns->glGenBuffers(1, &instanceVBO);
      m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
      m_glFuns-> glBufferData(GL_ARRAY_BUFFER, sizeof(QVector2D) * 100, &translations[0], GL_STATIC_DRAW);
      m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, 0);


    //创建VBO，VAO，EBO对象,并赋予id
    m_glFuns->glGenVertexArrays(1,&m_gldata.VAO);
    m_glFuns->glGenBuffers(1, &m_gldata.VBO);




    m_glFuns->glBindVertexArray(m_gldata.VAO);
    m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, m_gldata.VBO);



    m_glFuns->glBufferData(GL_ARRAY_BUFFER,sizeof(Data::quadVertices),&Data::quadVertices[0], GL_STATIC_DRAW);
    //m_glFuns->glBufferSubData(GL_ARRAY_BUFFER,0,sizeof(Data::quadVertices),&Data::quadVertices[0]);


//    m_glFuns->glBufferSubData(GL_ARRAY_BUFFER,sizeof(Data::vertices)/2,sizeof(Data::vertices)/2,&Data::vertices[sizeof(Data::vertices)/2/sizeof(float)]);

    m_glFuns->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)0);
    m_glFuns->glEnableVertexAttribArray(0);

    m_glFuns->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(sizeof(float)*2));
    m_glFuns->glEnableVertexAttribArray(1);

    m_glFuns->glBindVertexArray(0);

    if(m_glShader==nullptr)
        return;



      m_glFuns->glEnableVertexAttribArray(2);
      m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
      m_glFuns->glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);

      m_glFuns->glBindBuffer(GL_ARRAY_BUFFER, 0);
      m_glFuns->glVertexAttribDivisor(2, 1);




      //m_glShader->bind();
//    for(unsigned int i=0;i<100;i++)
//    {

//         std::string str="offsets[" + std::to_string(i) + "]";
//        m_glShader->setUniformValue(str.c_str(),translations[i]);
//    }
}

void Screen::Draw()
{
    if(m_glShader==nullptr)
        return;

    Draw(*m_glShader);
}
