#version 330 core
out vec4 FragColor;

in vec3 fcolor;
void main()
{
    FragColor =vec4(fcolor,1.0); //vec4(1.0); // 将向量的四个分量全部设置为1.0
}
