#ifndef SCENE_H
#define SCENE_H
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include <QOpenGLFunctions_3_3_Core>

class Scene
{
public:

    QVector3D m_position;

    QQuaternion m_rotation;
    float ShowPitch;
    float ShowYaw;
    float ShowRoll;

    QVector3D m_scale;




    void SetWorldLocation(const QVector3D& NewLoc);
    void SetWorldRotation(const QQuaternion& NewRot);
    void SetWorldScale(const QVector3D& NewScale);

    inline QVector3D GetWorldLocation() const
    {
        return this->m_position;
    }

    inline QQuaternion GetWorldRotation() const
    {
        return this->m_rotation;
    }

    inline QVector3D GetWorldScale()const
    {
        return this->m_scale;
    }

    QMatrix4x4 UpdateModelMat() const;



    Scene();

    Scene(QVector3D position,QQuaternion rotation,QVector3D scale):
        m_position(position),m_rotation(rotation),m_scale(scale)
    {

    }
};

#endif // SCENE_H
