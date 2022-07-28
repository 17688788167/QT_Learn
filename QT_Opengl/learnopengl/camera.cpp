#include "camera.h"

MyCamera::MyCamera()
{

}

QMatrix4x4 MyCamera::GetViewMat() const
{
    return QMatrix4x4();
}

QMatrix4x4 MyCamera::GetProjectionMat() const
{
    return QMatrix4x4();
}
