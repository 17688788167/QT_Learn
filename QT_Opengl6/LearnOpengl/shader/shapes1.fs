#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D m_Texture;
uniform sampler2D m_Texture1;
uniform sampler2D m_Texture2;
void main()
{
    FragColor = texture(m_Texture1,TexCoord);
   //FragColor = mix(texture(m_Texture,TexCoord),texture(m_Texture2,TexCoord),0.5);
}
