#ifndef SCENE_H
#define SCENE_H
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include <QOpenGLFunctions_3_3_Core>

class Scene
{
public:

    QVector3D position;

    QQuaternion rotation;
    float ShowPitch;
    float ShowYaw;
    float ShowRoll;

    void SetWorldLocation(const QVector3D& NewLoc);
    void SetWorldRotation(const QQuaternion& NewRot);

    inline QVector3D GetWorldLocation() const
    {
        return this->position;
    }

    inline QQuaternion GetWorldRotation() const
    {
        return this->rotation;
    }

    inline QMatrix4x4 GetModelMat() const
    {
        return QMatrix4x4();
    }


    Scene();
};

#endif // SCENE_H
