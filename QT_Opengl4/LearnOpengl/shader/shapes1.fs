#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D m_Texture;
void main()
{
    FragColor = vec4(1,0.5,0.5,1);
}
