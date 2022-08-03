#version 330 core


//受到不同的光照的影响程度
struct Material
{
    sampler2D diffuse;
    sampler2D specular;
    sampler2D emission;
    float shininess;
};
uniform Material material;

//一个光源提供的不同的光照强度与光源的位置


out vec4 FragColor;
in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

uniform vec3 viewPos;




struct DirLight
{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};
uniform DirLight dirlight;

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir,vec3 diffuseTexColor,vec3 specularTexColor);

struct PointLight
{
    vec3 position;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};






uniform PointLight pointLights[4];
vec3 CalcPointLight(PointLight light,vec3 normal,vec3 FragPos,vec3 viewDir,vec3 diffuseTexColor,vec3 specularTexColor);

struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float cutOn;

    float constant;
    float linear;
    float quadratic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

void CalcSpotLight(SpotLight light,vec3 normal,vec3 FragPos,vec3 viewDir,vec3 diffuseTexColor,vec3 specularTexColor);


void main()
{
//冯氏光照模型 环境光照ambient,漫反射光照Diffuse,镜面光照Specular


    vec3 diffuseTexColor=vec3(texture(material.diffuse,TexCoords));
    vec3 specularTexColor=vec3(texture(material.specular,TexCoords));
    vec3 emissionTexColor=vec3(texture(material.emission,TexCoords));


    vec3 norm=normalize(Normal);
    vec3 viewDir=normalize(viewPos-FragPos);

    vec3 result=CalcDirLight(dirlight,norm,viewDir,diffuseTexColor,specularTexColor);

    for(int i=0;i<4;i++)
    {
        result+=CalcPointLight(pointLights[i],norm,FragPos,viewDir,diffuseTexColor,specularTexColor);
    }

    result+=CalcSpotLight(SpotLight,norm,FragPos,viewDir,diffuseTexColor,specularTexColor);


    FragColor = vec4(result, 1.0);
}

vec3 CalcDirLight(DirLight light,vec3 normal,vec3 viewDir,vec3 diffuseTexColor,vec3 specularTexColor)
{
    vec3 lightDir=normalize(-light.direction);

    //漫反射着色

    float diff=max(dot(normal,lightDir),0.0);

    //镜面着色
    vec3 reflectDir=reflect(-light,normal);
    float spec=pow(max(dot(viewDir,reflect),0.0),material.shininess);

    //合并结果
    vec3 ambient  = light.ambient  *diffuseTexColor ;
    vec3 diffuse  = light.diffuse  * diff *diffuseTexColor ;
    vec3 specular = light.specular * spec * specularTexColor;
    return (ambient + diffuse + specular);
}


vec3 CalcPointLight(PointLight light,vec3 normal,vec3 FragPos,vec3 viewDir,vec3 diffuseTexColor,vec3 specularTexColor)
{
    vec3 lightDir = normalize(light.position - FragPos);

    //漫反射着色
    float diff = max(dot(normal, lightDir), 0.0);

    //镜面光着色
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    //点光源衰减
    float distance=length(light.position-FragPos);
    float attenuation=1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);

    //合并结果
    vec3 ambient  = light.ambient  *diffuseTexColor ;
    vec3 diffuse  = light.diffuse  * diff *diffuseTexColor ;
    vec3 specular = light.specular * spec * specularTexColor;

    return (ambient + diffuse + specular)*attenuation;
}

void CalcSpotLight(SpotLight light,vec3 normal,vec3 FragPos,vec3 viewDir,vec3 diffuseTexColor,vec3 specularTexColor)
{
     vec3 lightDir = normalize(light.position - FragPos);

     //漫反射着色
     float diff = max(dot(normal, lightDir), 0.0);

     //镜面光着色
     vec3 reflectDir = reflect(-lightDir, normal);
     float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

     //点光源衰减
     float distance=length(light.position-FragPos);
     float attenuation=1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);

     //合并结果
     vec3 ambient  = light.ambient  *diffuseTexColor ;
     vec3 diffuse  = light.diffuse  * diff *diffuseTexColor ;
     vec3 specular = light.specular * spec * specularTexColor;

     float theta=dot(lightDir,normalize(-light.direction));
     float alpha=smoothstep(light.cutOff,light.cutOn ,theta);

     diffuse*=alpha;
     specular*=alpha;


     return (ambient + diffuse + specular)*attenuation;

}
