#ifndef SCREEN_H
#define SCREEN_H
#include "iglbase.h"

class Screen:public IGLBase
{
public:
    Screen(QOpenGLFunctions_3_3_Core* glfun):IGLBase(glfun)
    {
    }

    virtual void Draw(QOpenGLShaderProgram &shader) override;
    virtual void setupMesh() override;
};

#endif // SCREEN_H
