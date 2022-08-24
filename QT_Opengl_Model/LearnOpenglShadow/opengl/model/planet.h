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
        setupMesh();
    }

    virtual void setupMesh() override;
    virtual void Draw(QOpenGLShaderProgram &shader)override;
    virtual void Draw()override;


    void Draw(QOpenGLShaderProgram &planetShader,QOpenGLShaderProgram &rockShader);
    unsigned int amount=50000;
    QMatrix4x4 *modelMatrices;

    Model* planet;
    Model* rock;
};

#endif // PLANET_H
