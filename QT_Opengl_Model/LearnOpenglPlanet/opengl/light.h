#ifndef LIGHT_H
#define LIGHT_H

enum LightType
{
    Directional,
    Point,
    Spot,
};



class Light
{
public:
    Light();

    LightType liteType;
};

#endif // LIGHT_H
