#include "mydepthtexture.h"
#include "myopenglwidget.h"


const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
MyDepthTexture::MyDepthTexture(QOpenGLFunctions_3_3_Core *glfuns, MyOpenglWidget *glwidget)
{
    m_glfuns=glfuns;
    m_glwidget=glwidget;
    initScreen();
    initFbo();
}

MyDepthTexture::MyDepthTexture()
{

}

void MyDepthTexture::initScreen()
{
    MyOpenglWidget::genShader(screenShaderProgram,":/shader/screen.vert",":/shader/screen.frag");


    m_glfuns->glGenVertexArrays(1,&VAO);
    m_glfuns->glGenBuffers(1, &VBO);

    m_glfuns->glBindVertexArray(VAO);
    m_glfuns->glBindBuffer(GL_ARRAY_BUFFER, VBO);

    m_glfuns->glBufferData(GL_ARRAY_BUFFER,sizeof(Data::quadVertices),&Data::quadVertices[0], GL_STATIC_DRAW);




    m_glfuns->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
    m_glfuns->glEnableVertexAttribArray(0);

    m_glfuns->glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(sizeof(float)*2));
    m_glfuns->glEnableVertexAttribArray(1);


    m_glfuns->glBindVertexArray(0);



     screenShaderProgram.bind();
     screenShaderProgram.setUniformValue("screenTexture", 0);
     screenShaderProgram.release();

       screenTexture=new QOpenGLTexture(QImage(":/iamge/container2.png").mirrored());
}

void MyDepthTexture::initFbo()
{

    MyOpenglWidget::genShader(m_DepthMapShaderProgram,":/shader/depthMap.vert",":/shader/depthMap.frag");

    m_glfuns->glGenFramebuffers(1, &depthMapFBO);
    // create depth texture
    unsigned int depthMap;
    m_glfuns->glGenTextures(1, &depthMap);
    m_glfuns->glBindTexture(GL_TEXTURE_2D, depthMap);
    m_glfuns->glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
    m_glfuns->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    m_glfuns->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    m_glfuns->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    m_glfuns->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // attach depth texture as FBO's depth buffer
    m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    m_glfuns->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
    m_glfuns->glDrawBuffer(GL_NONE);
    m_glfuns->glReadBuffer(GL_NONE);

    if (m_glfuns->glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        qDebug() << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << endl;
    m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER,m_glwidget->defaultFramebufferObject() );
}

void MyDepthTexture::paintFbo(const QMatrix4x4& lightSpaceMatrix)
{
   m_glfuns-> glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
   m_glfuns->glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
   m_glfuns-> glClear(GL_DEPTH_BUFFER_BIT);
   m_DepthMapShaderProgram.setUniformValue("lightSpaceMatrix", lightSpaceMatrix);




   m_glfuns-> glBindFramebuffer(GL_FRAMEBUFFER, m_glwidget-> defaultFramebufferObject());
   m_DepthMapShaderProgram.release();
}

void MyDepthTexture::paintScreen()
{
    screenShaderProgram.bind();
   m_glfuns-> glViewport(0, 0, m_glwidget-> width(),  m_glwidget->height());




     m_glfuns->glBindVertexArray(VAO);
        //screenTexture->bind(0);
     m_glfuns-> glActiveTexture(GL_TEXTURE0);
     m_glfuns-> glBindTexture(GL_TEXTURE_2D, depthMapFBO);	// use the color attachment texture as the texture of the quad plane


     m_glfuns-> glDrawArrays(GL_TRIANGLES, 0, 6);

screenShaderProgram.release();

}
