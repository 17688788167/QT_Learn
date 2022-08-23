#ifndef CUBE_H
#define CUBE_H
#include "iglbase.h"

class CubeActor :public IGLBase
{
public:
    CubeActor(QOpenGLFunctions_3_3_Core * glfun):IGLBase(glfun)
    {
        setupMesh();
    }

    virtual void Draw(QOpenGLShaderProgram &shader) override;
    virtual void setupMesh() override;
    virtual void Draw()override;


};

#endif // CUBE_H
