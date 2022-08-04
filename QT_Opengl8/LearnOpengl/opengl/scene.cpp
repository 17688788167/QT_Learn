#include "scene.h"

void Scene::SetWorldLocation(const QVector3D &NewLoc)
{
    this->m_position=NewLoc;

}

void Scene::SetWorldRotation(const  glm::quat &NewRot)
{
    this->m_rotation=NewRot;
}

void Scene::SetWorldScale(const QVector3D &NewScale)
{
    this->m_scale=NewScale;
}

QMatrix4x4 Scene::UpdateModelMat() const
{
    {
        QMatrix4x4 trans;


        trans.translate(m_position);
        //trans.rotate(m_rotation);
        trans.scale(m_scale);
        return trans;
    }
}

Scene::Scene()
{

}
