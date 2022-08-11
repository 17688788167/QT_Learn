#ifndef DATA_H
#define DATA_H
#include <QVector>
#include <QVector3D>
#include <vector>
enum EShape
{
    None,
    Rect,
    Circle,
    Triangle

};


struct FGLData
{
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;
};

class Data
{
public:
    constexpr static unsigned int SCR_WIDTH = 800;
    constexpr static unsigned int SCR_HEIGHT = 600;

    constexpr static float vertices1[] = {
    -0.5f, -0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
     0.0f,  0.5f, 0.0f
    };

    constexpr static float vertices2[] = {
    0.5f,  0.5f,  0.0f,
    -0.5f, 0.8f, 0.0f,
     0.0f, 0.5f, 0.0f
    };


    constexpr static  float verticesAndTexCoords[] = {
        // Back face
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        // Front face
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // Left face
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
        // Right face
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
        // Bottom face
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
        // Top face
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left
    };
    constexpr static  float cubeVertices[] = {
        // Back face
        -0.5f, -0.5f, -0.5f,  //0.0f, 0.0f, // Bottom-left
         0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  //1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  //0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, // top-left
        // Front face
        -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  //1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  //1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  //1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  //0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f, // bottom-left
        // Left face
        -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // top-right
        // Right face
         0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // top-left
         0.5f, -0.5f,  0.5f, // 0.0f, 0.0f, // bottom-left
        // Bottom face
        -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  //1.0f, 1.0f, // top-left
         0.5f, -0.5f,  0.5f,  //1.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  //1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // top-right
        // Top face
        -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, // top-left
         0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, // top-left
        -0.5f,  0.5f,  0.5f  //0.0f, 0.0f  // bottom-left
    };

    constexpr static  float vertices[] = {
        -0.5f, -0.5f, -0.5f,  //0.0f, 0.0f, // Bottom-left
         0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  //1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-right
        -0.5f, -0.5f, -0.5f,  //0.0f, 0.0f, // bottom-left
        -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, // top-left
        // Front face
        -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  //1.0f, 0.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  //1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  //1.0f, 1.0f, // top-right
        -0.5f,  0.5f,  0.5f,  //0.0f, 1.0f, // top-left
        -0.5f, -0.5f,  0.5f, // 0.0f, 0.0f, // bottom-left
        // Left face
        -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // top-right
        -0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-left
        -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f, // bottom-right
        -0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // top-right
        // Right face
         0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // top-left
         0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // bottom-right
         0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // top-left
         0.5f, -0.5f,  0.5f, // 0.0f, 0.0f, // bottom-left
        // Bottom face
        -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // top-right
         0.5f, -0.5f, -0.5f,  //1.0f, 1.0f, // top-left
         0.5f, -0.5f,  0.5f,  //1.0f, 0.0f, // bottom-left
         0.5f, -0.5f,  0.5f,  //1.0f, 0.0f, // bottom-left
        -0.5f, -0.5f,  0.5f,  //0.0f, 0.0f, // bottom-right
        -0.5f, -0.5f, -0.5f,  //0.0f, 1.0f, // top-right
        // Top face
        -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, // top-left
         0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // bottom-right
         0.5f,  0.5f, -0.5f,  //1.0f, 1.0f, // top-right
         0.5f,  0.5f,  0.5f,  //1.0f, 0.0f, // bottom-right
        -0.5f,  0.5f, -0.5f,  //0.0f, 1.0f, // top-left
        -0.5f,  0.5f,  0.5f  //0.0f, 0.0f  // bottom-left
    };



};



#endif // DATA_H
