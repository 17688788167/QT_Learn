#include "scene.h"

void Scene::SetWorldLocation(const QVector3D &NewLoc)
{
    this->position=NewLoc;

}

void Scene::SetWorldRotation(const QQuaternion &NewRot)
{
    this->rotation=NewRot;
}

Scene::Scene()
{

}
