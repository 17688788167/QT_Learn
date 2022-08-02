#version 330 core


//受到不同的光照的影响程度
struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
uniform Material material;

//一个光源提供的不同的光照强度与光源的位置
struct Light
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform Light light;

out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
//uniform vec3 lightColor;
//uniform vec3 lithtPos;
uniform vec3 viewPos;



void main()
{
//冯氏光照模型 环境光照ambient,漫反射光照Diffuse,镜面光照Specular
//环境光照ambient
    vec3 ambient=light.ambient*material.ambient;

//漫反射光照Diffuse,
    vec3 norm=normalize(Normal);
    vec3 lithtDir=normalize(light.position-FragPos);
    float diff = max(dot(norm,lithtDir),0.0);
    vec3 diffuse=light.diffuse*(diff*material.diffuse);

//镜面光照Specular
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lithtDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0),material.shininess);
    vec3 specular=light.specular*(spec*material.specular);

//求和
    vec3 result=(ambient+diffuse+specular);
    FragColor = vec4(result, 1.0);
}
