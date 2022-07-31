#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCord;

out vec2 TexCoord;

uniform mat4 modelMat;
void main()
{
    gl_Position =vec4(aPos.x, aPos.y, aPos.z, 1.0);
    TexCoord=vec2(1-aTexCord.s,aTexCord.t);
    //TexCoord=aTexCord;
}
