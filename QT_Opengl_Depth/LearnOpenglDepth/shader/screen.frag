#version 330 core
in vec3 Pos;
in vec2 TexCoords;
out vec4 FragColor;
uniform sampler2D texture1;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;

    float shininess;
};

uniform Material material;
void main()
{

    vec4 texColor=texture(material.texture_diffuse1,TexCoords);

    if(texColor.a<0.1)
        discard;
    FragColor = texColor;//vec4(1.0); // 将向量的四个分量全部设置为1.0
}
