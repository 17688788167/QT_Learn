#version 330 core
in vec3 Pos;
out vec4 FragColor;
uniform vec3 lightColor;


void main()
{

    FragColor =vec4(1.0,1.0,0.0,1.0); //vec4(1.0); // 将向量的四个分量全部设置为1.0
}
