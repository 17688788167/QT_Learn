#ifndef XXOPENGLWIDGET_H
#define XXOPENGLWIDGET_H
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QWidget>

class XXOpenGlWidget : public QOpenGLWidget,QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit XXOpenGlWidget(QWidget *parent = nullptr);
protected:
    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();


signals:

public slots:
};

#endif // XXOPENGLWIDGET_H
