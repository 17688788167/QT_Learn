#include "planet.h"
#include "time.h"


void Planet::setupMesh()
{

    string path="../model/planet/planet.obj";
    //QString path=
    planet=new Model(m_glFuns,path.c_str());

    path="../model/rock/rock.obj";
    rock=new Model(m_glFuns,path.c_str());

    modelMatrices=new QMatrix4x4[amount];
    QVector4D* qvector4d=new QVector4D[4*amount];
    std::srand(time(NULL));
    float radius=150.0f;
    float offset=25.0f;
    for(unsigned int i=0;i<amount;i++)
    {
        QMatrix4x4 model;

        // 1. 位移：分布在半径为 'radius' 的圆形上，偏移的范围是 [-offset, offset]
        float angle=(float)i/(float)amount*360.0f;
        //使displacrment在-2.5~2.5之间
        float displacrment=(std::rand()%(int)(2*offset*100))/100.0f-offset;
        float x=std::sin(angle)*radius+displacrment;

         displacrment=(std::rand()%(int)(2*offset*100))/100.0f-offset;
         float y=displacrment*0.4f;

         displacrment=(std::rand()%(int)(2*offset*100))/100.0f-offset;
         float z=std::cos(angle)*radius+displacrment;

         model.setToIdentity();
         model.translate(x,y,z);

          // 2. 缩放：在 0.05 和 0.25f 之间缩放
         float scale=std::rand()%20/100.0f+0.05f;
         model.scale(scale);

         // 3. 旋转：绕着一个（半）随机选择的旋转轴向量进行随机的旋转
         float rotAngle=(std::rand()%360);
         model.rotate(rotAngle,QVector3D(0.4f,0.6f,0.8f));

         modelMatrices[i]=model;


         for(unsigned int j=0;j<4;j++)
         qvector4d[i*4+j]=model.column(j);


    }

    unsigned int buffer;
    m_glFuns-> glGenBuffers(1,&buffer);
    m_glFuns-> glBindBuffer(GL_ARRAY_BUFFER, buffer);
    m_glFuns-> glBufferData(GL_ARRAY_BUFFER, amount * 64, &qvector4d[0], GL_STATIC_DRAW);

    for(unsigned int i=0;i<rock->meshes.size();i++)
    {
        unsigned int VAO = rock->meshes[i]->m_gldata.VAO;
        m_glFuns->glBindVertexArray(VAO);


       std::size_t vec4Size=sizeof(QVector4D);
       m_glFuns-> glEnableVertexAttribArray(3);
       m_glFuns-> glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
       m_glFuns-> glEnableVertexAttribArray(4);
       m_glFuns-> glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(1 * vec4Size));
       m_glFuns-> glEnableVertexAttribArray(5);
       m_glFuns-> glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
       m_glFuns-> glEnableVertexAttribArray(6);
       m_glFuns-> glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
       m_glFuns->glVertexAttribDivisor(3, 1);
       m_glFuns->glVertexAttribDivisor(4, 1);
       m_glFuns->glVertexAttribDivisor(5, 1);
       m_glFuns-> glVertexAttribDivisor(6, 1);
       m_glFuns-> glBindVertexArray(0);
    }
}

void Planet::Draw(QOpenGLShaderProgram &shader)
{
    shader.bind();




    rock->Draw(shader);




//    for(unsigned int i=0;i<amount;i++)
//    {
//        shader.bind();s
//    }



}

void Planet::Draw()
{

}

void Planet::Draw(QOpenGLShaderProgram &planetShader, QOpenGLShaderProgram &rockShader)
{
    planetShader.bind();
    if(planet!=NULL)
    {
        QMatrix4x4 model;
        model.setToIdentity();
        model.translate(0,-10,0);
        model.scale(10);
        planetShader.setUniformValue("model",model);
        planet->Draw(planetShader);
    }

    if(rock!=NULL)
    {
//            for(unsigned int i=0;i<amount;i++)
//            {
//                rockShader.bind();
//                rockShader.setUniformValue("model",modelMatrices[i]);
//                rock->Draw(rockShader);
//            }
        //qDebug()<<"dddddd";

         rockShader.bind();
       rock->DrawInstance(rockShader,amount);
    }
}
