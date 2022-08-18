#ifndef SCREEN_H
#define SCREEN_H
#include "iglbase.h"

class Screen:public IGLBase
{
public:
    Screen(QOpenGLFunctions_3_3_Core* glfun):IGLBase(glfun)
    {
        setupMesh();
    }

    Screen(QOpenGLFunctions_3_3_Core* glfun,QOpenGLShaderProgram*glShader):IGLBase(glfun,glShader)
    {
        setupMesh();
    }

    virtual void Draw(QOpenGLShaderProgram &shader) override;
    virtual void setupMesh() override;
    virtual void Draw()override;

    unsigned int instanceVBO;
};

#endif // SCREEN_H
