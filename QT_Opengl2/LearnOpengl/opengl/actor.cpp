#include "actor.h"
#include <QDebug>

Actor::Actor()
{

}

Actor::Actor(float Scale, float xOffset, float yOffset)
{
    GenModelVerticesData(Scale,xOffset,yOffset);

    //BindVAOVBO();


}

Actor::~Actor()
{
    if(ModelVertices)
    {
     delete ModelVertices;
     ModelVertices=nullptr;
    }
}


void Actor::GenModelVerticesData(float Scale, float xOffset, float yOffset)
{
    int num = sizeof(Data::verticesAndTexCoords) / sizeof(float);
            ModelVertices = new float[num];
            for (int i = 0; i < num; ++i)
            {
                if (i%5<3)
                {
                  ModelVertices[i] =  Data::verticesAndTexCoords[i]*Scale;
                }

                if (i % 5 == 0)
                {
                    ModelVertices[i] += xOffset;

                }
                else if (i % 5 == 1)
                {
                    ModelVertices[i] += yOffset;

                }
                else if (i % 5 == 2)
                {

                }
            }
}

void Actor::DrawActor()
{

}
