#ifndef GEOMETRY_H
#define GEOMETRY_H
#include "iglbase.h"

class Geometry:public IGLBase
{
public:
    Geometry(QOpenGLFunctions_3_3_Core * glfun):IGLBase(glfun)
    {
        setupMesh();
    }

    virtual void Draw(QOpenGLShaderProgram &shader) override;
    virtual void setupMesh() override;
    virtual void Draw()override;
};

#endif // GEOMETRY_H
