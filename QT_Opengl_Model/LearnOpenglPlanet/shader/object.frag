#version 420 core

//layout (depth_greater) out float gl_FragDepth;

in VS_OUT
{
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
}fs_in;
//受到不同的光照的影响程度
struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    sampler2D texture_reflection1;
    float shininess;
};
uniform Material material;

//一个光源提供的不同的光照强度与光源的位置
struct SpotLight
{
    vec3 position;
    vec3 direction;

    float cutOff;
    float cutOn;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotlight;
vec3 CalcSpotLightColor(SpotLight light);


struct DirectLight
{

    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform DirectLight directlight;
vec3 CalcDirectLightColor(DirectLight light);

struct PointLight
{
    vec3 position;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};


#define NR_POINT_LIGHTS 4
uniform PointLight[NR_POINT_LIGHTS] pointlight;
vec3 CalcPointLightColor(PointLight light);


out vec4 FragColor;


uniform vec3 objectColor;
uniform vec3 viewPos;
//uniform samplerCube skybox;

vec3 diffuseTexColor=vec3(texture(material.texture_diffuse1,fs_in.TexCoords));
vec3 specularTexColor=vec3(texture(material.texture_specular1,fs_in.TexCoords));
vec3 reflectionTexColor=vec3(texture(material.texture_reflection1,fs_in.TexCoords));
//vec3 emissionTexColor=vec3(texture(material.emission,fs_in.TexCoords));

vec3 norm=normalize(fs_in.Normal);
vec3 viewDir=normalize(viewPos-fs_in.FragPos);


void main()
{
//冯氏光照模型 环境光照ambient,漫反射光照Diffuse,镜面光照Specular
    vec3 result=vec3(0,0,0);
    result += CalcSpotLightColor(spotlight);
    result += CalcDirectLightColor(directlight);

//    for(int i=0; i<NR_POINT_LIGHTS;++i)
//    {
        result+=CalcPointLightColor(pointlight[0]);
//    }
       // vec3 I = normalize(fs_in.FragPos - viewPos);
       // vec3 R = reflect(I, normalize(fs_in.Normal));
       // vec3 reflectionSkyBox=texture(skybox,R).rgb;
       // vec3 reflection=reflectionSkyBox*reflectionTexColor;
    //result+=reflection;
    FragColor = vec4(result, 1.0);

    //gl_FragDepth = gl_FragCoord.z + 0.1;
}

vec3 CalcSpotLightColor(SpotLight light)
{
    //点光源会根据距离进行衰减，衰减的值用一个二次方程表示，并让环境光，漫反射光，镜面反射光都*=衰减因子
    float distance=length(light.position-fs_in.FragPos);
    float attenuation=1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);

    //环境光照ambient
    vec3 ambient=light.ambient*diffuseTexColor;
    ambient*=attenuation;

    //漫反射光照
    vec3 lightDir=normalize(light.position-fs_in.FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse=light.diffuse*diff*diffuseTexColor;
    diffuse*=attenuation;

    //镜面光照
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0),material.shininess);
    vec3 specular=light.specular*spec*specularTexColor;
    specular*=attenuation;

    float theta=dot(lightDir,normalize(-light.direction));
    float alpha=smoothstep(light.cutOff,light.cutOn ,theta);

    diffuse*=alpha;
    specular*=alpha;
    //return vec3(1,1,1);
    return ambient+diffuse+specular;
    //return light.ambient+light.diffuse+light.specular;
}

vec3 CalcDirectLightColor(DirectLight light)
{
    //环境光照ambient
    vec3 ambient=light.ambient*diffuseTexColor;

    //漫反射光照
     vec3 lightDir=normalize(-light.direction);
     float diff = max(dot(norm,lightDir),0.0);
     vec3 diffuse=light.diffuse*diff*diffuseTexColor;

     //镜面光照
     vec3 reflectDir=reflect(-lightDir,norm);
     float spec=pow(max(dot(viewDir,reflectDir),0),material.shininess);
     vec3 specular=light.specular*spec*specularTexColor;

      return ambient+diffuse+specular;
}

vec3 CalcPointLightColor(PointLight light)
{
    //点光源会根据距离进行衰减，衰减的值用一个二次方程表示，并让环境光，漫反射光，镜面反射光都*=衰减因子
    float distance=length(light.position-fs_in.FragPos);
    float attenuation=1.0/(light.constant+light.linear*distance+light.quadratic*distance*distance);

    //环境光照ambient
    vec3 ambient=light.ambient*diffuseTexColor;
    ambient*=attenuation;

    //漫反射光照
    vec3 lightDir=normalize(light.position-fs_in.FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse=light.diffuse*diff*diffuseTexColor;
    diffuse*=attenuation;

    //镜面光照
    vec3 reflectDir=reflect(-lightDir,norm);
    float spec=pow(max(dot(viewDir,reflectDir),0),material.shininess);
    vec3 specular=light.specular*spec*specularTexColor;
    specular*=attenuation;
    //return vec3(0,0,0);
    //return vec3(0.1,0.1,0.1);
    return ambient+diffuse+specular;
}

