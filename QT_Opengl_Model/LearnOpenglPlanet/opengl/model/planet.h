#ifndef PLANET_H
#define PLANET_H
#include "model.h"
#include "iglbase.h"
#include <QMatrix4x4>

class Planet: public IGLBase
{
public:
    Planet(QOpenGLFunctions_3_3_Core* glFuns):IGLBase(glFuns)
    {

    }

    virtual void setupMesh() override;
    virtual void Draw(QOpenGLShaderProgram &shader)override;
    virtual void Draw()override;

    unsigned int amount=10000;
    QMatrix4x4 *modelMatrices;

    Model* planet;
    Model* rock;
};

#endif // PLANET_H
