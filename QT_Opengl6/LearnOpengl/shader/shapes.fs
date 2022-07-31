#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D m_Texture;
uniform sampler2D m_Texture1;
uniform sampler2D m_Texture2;

uniform float ratio;
void main()
{
    //FragColor = texture(m_Texture2,TexCoord);
    FragColor=mix(texture(m_Texture1,TexCoord),texture(m_Texture,TexCoord),ratio);

}
 
