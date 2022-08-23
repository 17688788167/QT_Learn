#ifndef PLANE_H
#define PLANE_H
#include "iglbase.h"

class Plane:public IGLBase
{
public:
    Plane(QOpenGLFunctions_3_3_Core * glfun):IGLBase(glfun)
    {
        setupMesh();
    }

    virtual void Draw(QOpenGLShaderProgram &shader) override;
    virtual void setupMesh() override;
    virtual void Draw()override;

};

#endif // PLANE_H
