#include "actor.h"
#include "data.h"

using namespace std;
Actor::Actor()
{

}

Actor::~Actor()
{

    delete ModelVertices;
    ModelVertices=nullptr;
}

void Actor::DrawActor()
{
    glBindVertexArray(ActorVAO);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Actor::GenModelVerticesData(float Scale, float xOffset, float yOffset)
{
    glGenVertexArrays(1, &ActorVAO);
    glGenBuffers(1, &ActorVBO);

    glBindVertexArray(ActorVAO);
    glBindBuffer(GL_ARRAY_BUFFER, ActorVBO);
//    cout << sizeof(ActorVertices) << endl;
//    cout << sizeof(Data::vertices) << endl;
    glBufferData(GL_ARRAY_BUFFER, sizeof(Data::verticesAndTexCoords), ModelVertices, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

            //glBufferData(GL_ARRAY_BUFFER, sizeof(Data::verticesAndTexCoords), Data::verticesAndTexCoords, GL_STATIC_DRAW);
     glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)3);
     glEnableVertexAttribArray(1);
}
