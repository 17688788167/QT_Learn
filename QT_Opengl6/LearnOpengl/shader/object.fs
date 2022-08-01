#version 330 core
out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lithtPos;
uniform vec3 viewPos;



void main()
{
//冯氏光照模型 环境光照ambient,漫反射光照Diffuse,镜面光照Specular
//环境光照ambient
    float ambientStrength=0.1;
    vec3 ambient=ambientStrength*lightColor;

//漫反射光照Diffuse,
    vec3 norm=normalize(Normal);
    vec3 lithtDir=normalize(lithtPos-FragPos);
    float diff = max(dot(norm,lithtDir),0.0);
    vec3 diffuse=diff*lightColor;

//镜面光照Specular
    float specularStrength =0.5f;
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lithtDir,norm);

    float spec=pow(max(dot(viewDir,reflectDir),0),32);
    vec3 specular=specularStrength*spec*lightColor;

//求和
    vec3 result=(ambient+diffuse+specular)*objectColor;
    FragColor = vec4(result, 1.0);
}
