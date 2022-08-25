#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;


layout(std140) uniform Matrices
{
  mat4 projection;
  mat4 view;
};

out VS_OUT
{
    vec3 Normal;
    vec3 FragPos;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
}vs_out;

uniform mat4 model;
uniform mat4 lightSpaceMatrix;
uniform bool reverse_normals;

void main()
{
   vs_out.Normal = mat3(transpose(inverse(model))) * aNormal;
   vs_out.FragPos=vec3(model*vec4(aPos,1));

   if(reverse_normals) // a slight hack to make sure the outer large cube displays lighting from the 'inside' instead of the default 'outside'.
       vs_out.Normal = transpose(inverse(mat3(model))) * (-1.0 * aNormal);
   else
       vs_out.Normal = transpose(inverse(mat3(model))) * aNormal;


   vs_out.TexCoords=aTexCoords;
   vs_out.FragPosLightSpace=lightSpaceMatrix*vec4(vs_out.FragPos,1.0);
   gl_Position =projection* view* model*vec4(aPos, 1.0);

}
