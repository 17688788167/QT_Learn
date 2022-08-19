#include "planet.h"
#include "time.h"


void Planet::setupMesh()
{
    modelMatrices=new QMatrix4x4[amount];
    QVector4D* qvector4d=new QVector4D[4*amount];
    std::srand(time(NULL));
    float radius=50.0f;
    float offset=2.5f;
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
    }


    rock=new Model(m_glFuns,":/model/model/rock/rock.obj");

}

void Planet::Draw(QOpenGLShaderProgram &shader)
{
    shader.bind();
    planet->Draw(shader);


}

void Planet::Draw()
{

}
