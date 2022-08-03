#ifndef SCENE_H
#define SCENE_H
#include <QVector3D>
#include <QQuaternion>
#include <QMatrix4x4>
#include <QOpenGLFunctions_3_3_Core>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

  const QVector3D WorldUp=QVector3D(0,1,0);
  const QVector3D WorldForward=QVector3D(0,0,1);
  const QVector3D WorldRight=QVector3D(1,0,0);

class Scene
{
public:

   // Scene(QVector3D position, QQuaternion rotation, QVector3D scale);

    QVector3D m_position;

    glm::quat m_rotation;

    float ShowPitch;
    float ShowYaw;
    float ShowRoll;

    QVector3D m_scale;




    void SetWorldLocation(const QVector3D& NewLoc);
    void SetWorldRotation(const  glm::quat& NewRot);
    void SetWorldScale(const QVector3D& NewScale);

    inline QVector3D GetWorldLocation() const
    {
        return this->m_position;
        //m_rotation.rotatedVector()
        //QQuaternion::rotatedVector()


    }

    inline glm::quat GetWorldRotation() const
    {
        return this->m_rotation;
    }

    inline QVector3D GetWorldScale()const
    {
        return this->m_scale;
    }

    QMatrix4x4 UpdateModelMat() const;



    Scene();

    Scene(QVector3D position, glm::quat rotation,QVector3D scale):
        m_position(position),m_rotation(rotation),m_scale(scale)
    {

    }
};

#endif // SCENE_H
