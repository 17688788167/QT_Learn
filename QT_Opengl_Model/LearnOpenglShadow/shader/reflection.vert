#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;

out vec3 Normal;
out vec3 Position;

layout(std140) uniform Matrices
{
  mat4 projection;
  mat4 view;
};

uniform mat4 model;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Position=vec3(model*vec4(aPos,1));
    gl_Position =projection* view* model*vec4(aPos, 1.0);

}