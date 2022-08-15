#version 330 core
in vec2 TexCoords;
out vec4 FragColor;




uniform sampler2D screenTexture;

const float offset=1.0/300.0;

void main()
{

    vec2 offsets[9] = vec2[](
        vec2(-offset,  offset), // 左上
        vec2( 0.0f,    offset), // 正上
        vec2( offset,  offset), // 右上
        vec2(-offset,  0.0f),   // 左
        vec2( 0.0f,    0.0f),   // 中
        vec2( offset,  0.0f),   // 右
        vec2(-offset, -offset), // 左下
        vec2( 0.0f,   -offset), // 正下
        vec2( offset, -offset)  // 右下
    );

    float kernel[9] = float[](
        1, 1, 1,
        1,  -8, 1,
        1, 1, 1
    );
    vec4 texColor=texture(screenTexture,TexCoords);
    vec3 result;
    //1.反相
    //result=vec4(1-result,1.0) ;

    //2.灰度
   //float average=0.2126*texColor.r+0.7152*texColor.g+0.0722*texColor.b;
    //result=vec4(average,average,average,1.0);

//    vec3 sampleTex[9];
//    for(int i=0; i<9;i++)
//    {
//        sampleTex[i] = vec3(texture(screenTexture, TexCoords.st + offsets[i]));
//        result+=sampleTex[i]*kernel[i];
//    }

    FragColor = texColor;//vec4(result,1.0);//vec4(1.0); // 将向量的四个分量全部设置为1.0
}
