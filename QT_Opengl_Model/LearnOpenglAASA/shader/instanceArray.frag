#version 330 core
out vec4 FragColor;


in VS_OUT{
  vec3 fColor;
}fs_in;


void main()
{
    //FragColor =vec4(1.0);// // // 将向量的四个分量全部设置为1.0
    FragColor =vec4(fs_in.fColor,1.0);
}
