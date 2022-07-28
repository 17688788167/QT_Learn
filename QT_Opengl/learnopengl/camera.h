#ifndef MYCAMERA_H
#define MYCAMERA_H
#include <scene.h>
class MyCamera : public Scene
{
public:
    MyCamera();

    QMatrix4x4 GetViewMat() const;


    QMatrix4x4 GetProjectionMat() const;


};

#endif // CAMERA_H
