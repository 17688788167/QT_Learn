#include "pointdepthtexture.h"
#include "myopenglwidget.h"
#include <QMatrix4x4>
PointDepthTexture::PointDepthTexture()
{

}

PointDepthTexture::PointDepthTexture(QOpenGLFunctions_3_3_Core *glfuns, MyOpenglWidget *glwidget)
{
    m_glfuns=glfuns;
    m_glwidget=glwidget;
    initScreen();
    initFbo();
    lightPos=m_glwidget->lightPos;
}

void PointDepthTexture::initScreen()
{

}

void PointDepthTexture::initFbo()
{
    MyOpenglWidget::genShader(m_DepthMapShaderProgram,":/shader/pointdepthMap.vert",":/shader/pointdepthMap.frag",":/shader/pointdepthMap.geom");


    m_glfuns->glGenFramebuffers(1, &depthMapFBO);
    m_glfuns->glGenTextures(1, &depthCubemap);
    m_glfuns->glBindTexture(GL_TEXTURE_CUBE_MAP, depthCubemap);

    for(unsigned int i=0;i<6;++i)
    {
        m_glfuns->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT,
                            SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    }

    m_glfuns->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    m_glfuns->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    m_glfuns->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    m_glfuns->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    m_glfuns->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);


    m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    m_glfuns->glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, depthCubemap, 0);
    m_glfuns->glDrawBuffer(GL_NONE);
    m_glfuns->glReadBuffer(GL_NONE);
    m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER, m_glwidget->defaultFramebufferObject());

    if (m_glfuns->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER, m_glwidget->defaultFramebufferObject());
}

void PointDepthTexture::paintFbo()
{
    float near_plane = 1.0f;
    float far_plane  = 25.0f;
    QMatrix4x4 shadowProj;
    QMatrix4x4 shadowView;

    shadowProj.perspective(90.0f, (float)SHADOW_WIDTH / (float)SHADOW_HEIGHT, near_plane, far_plane);
    std::vector<QMatrix4x4> shadowTransforms;
    shadowView.lookAt(lightPos, lightPos + QVector3D( 1.0, 0.0, 0.0), QVector3D(0.0,-1.0, 0.0));
    shadowTransforms.push_back(shadowProj * shadowView);
    shadowView.setToIdentity();

    shadowView.lookAt(lightPos, lightPos + QVector3D(-1.0, 0.0, 0.0), QVector3D(0.0,-1.0, 0.0));
    shadowTransforms.push_back(shadowProj * shadowView);
    shadowView.setToIdentity();
    shadowView.lookAt(lightPos, lightPos + QVector3D( 0.0, 1.0, 0.0), QVector3D(0.0, 0.0, 1.0));
    shadowTransforms.push_back(shadowProj * shadowView);
    shadowView.setToIdentity();
    shadowView.lookAt(lightPos, lightPos + QVector3D( 0.0,-1.0, 0.0), QVector3D(0.0, 0.0,-1.0));
    shadowTransforms.push_back(shadowProj * shadowView);
    shadowView.setToIdentity();
    shadowView.lookAt(lightPos, lightPos + QVector3D( 0.0, 0.0, 1.0), QVector3D(0.0,-1.0, 0.0));
    shadowTransforms.push_back(shadowProj * shadowView);
    shadowView.setToIdentity();
    shadowView.lookAt(lightPos, lightPos + QVector3D( 0.0, 0.0,-1.0), QVector3D(0.0,-1.0, 0.0));
    shadowTransforms.push_back(shadowProj * shadowView);

     // 1. render scene to depth cubemap
    m_glfuns->glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    m_glfuns->glClear(GL_DEPTH_BUFFER_BIT);
    m_DepthMapShaderProgram.bind();
    m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    m_glfuns->glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
    m_glfuns->glClear(GL_DEPTH_BUFFER_BIT);

    for (unsigned int i = 0; i < 6; ++i){
        std::string str="shadowMatrices[" + std::to_string(i) + "]";
        m_DepthMapShaderProgram.setUniformValue(str.c_str(), shadowTransforms[i]);
    }
    m_DepthMapShaderProgram.setUniformValue("far_plane", far_plane);
    m_DepthMapShaderProgram.setUniformValue("lightPos", lightPos);

    m_glwidget->renderScene(m_DepthMapShaderProgram);
    m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER,m_glwidget-> defaultFramebufferObject());
    m_DepthMapShaderProgram.release();

}

void PointDepthTexture::paintScreen()
{

}
