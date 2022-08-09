#version 330 core

out vec4 FragColor;


float near =0.1;
float far=100.0;
float linearizeDepth(float depth)
{
    float z_ndc=depth*2.0-1.0;

    return (2.0*near*far)/(far+near-z_ndc*(far-near));
}

void main()
{
//冯氏光照模型 环境光照ambient,漫反射光照Diffuse,镜面光照Specular
    vec3 result=vec3(0,0,0);
    float depth=(linearizeDepth(gl_FragCoord.z)-near)/(far-near);
    result=vec3(depth);
    FragColor = vec4(result, 1.0);
}

