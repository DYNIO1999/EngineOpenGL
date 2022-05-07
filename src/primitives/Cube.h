#ifndef DENGINE_CUBE_H
#define DENGINE_CUBE_H
#include "renderer/Mesh.h"


namespace DEngine{


class Cube : public Mesh{
public:
    Cube(): Mesh({
        //bottom
        {
                glm::vec3{-1.0f,-1.0f,-1.0f},
                glm::vec3{0.0f,-1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 0.0f}
        },
        {
                glm::vec3{ 1.0f,-1.0f,-1.0f},
                glm::vec3{0.0f,-1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{-1.0f,-1.0f, 1.0f},
                glm::vec3{0.0f,-1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{ 0.0f, 1.0f}
        },
        {
                glm::vec3{1.0f,-1.0f,-1.0f},
                glm::vec3{0.0f,-1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{ 1.0f,-1.0f, 1.0f },
                glm::vec3{0.0f,-1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{ 1.0f, 1.0f}
        },
        {
                glm::vec3{ -1.0f,-1.0f, 1.0f},
                glm::vec3{0.0f,-1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{ 0.0f, 1.0f}
        },

        //top
        {
                glm::vec3{-1.0f, 1.0f,-1.0f},
                glm::vec3{0.0f,1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 0.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f, 1.0f},
                glm::vec3{0.0f,1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 1.0f}
        },
        {
                glm::vec3{1.0f, 1.0f,-1.0f},
                glm::vec3{0.0f,1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{1.0f, 1.0f,-1.0f},
                glm::vec3{0.0f,1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f, 1.0f},
                glm::vec3{0.0f,1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 1.0f}
        },
        {
                glm::vec3{1.0f, 1.0f, 1.0f},
                glm::vec3{0.0f,1.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 1.0f}
        },
        //front
        {
                glm::vec3{-1.0f,-1.0f, 1.0f},
                glm::vec3{0.0f,0.0f,1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{1.0f,-1.0f, 1.0f},
                glm::vec3{0.0f,0.0f,1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 0.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f, 1.0f},
                glm::vec3{0.0f,0.0f,1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 1.0f}
        },
        {
                glm::vec3{1.0f,-1.0f, 1.0f},
                glm::vec3{0.0f,0.0f,1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 0.0f}
        },
        {
                glm::vec3{1.0f, 1.0f, 1.0f},
                glm::vec3{0.0f,0.0f,1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 1.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f, 1.0f},
                glm::vec3{0.0f,0.0f,1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 1.0f}
        },
        //back
        {
                glm::vec3{-1.0f,-1.0f,-1.0f},
                glm::vec3{0.0f,0.0f,-1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 0.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f,-1.0f},
                glm::vec3{0.0f,0.0f,-1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 1.0f}
        },
        {
                glm::vec3{1.0f,-1.0f,-1.0f},
                glm::vec3{0.0f,0.0f,-1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{1.0f,-1.0f,-1.0f},
                glm::vec3{0.0f,0.0f,-1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f,-1.0f},
                glm::vec3{0.0f,0.0f,-1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 1.0f}
        },
        {
                glm::vec3{1.0f, 1.0f,-1.0f},
                glm::vec3{0.0f,0.0f,-1.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 1.0f}
        },
        //left
        {
                glm::vec3{-1.0f,-1.0f, 1.0f},
                glm::vec3{-1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 1.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f,-1.0f},
                glm::vec3{-1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{-1.0f,-1.0f,-1.0f},
                glm::vec3{-1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 0.0f}
        },
        {
                glm::vec3{-1.0f,-1.0f, 1.0f},
                glm::vec3{-1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 1.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f, 1.0f},
                glm::vec3{-1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 1.0f}
        },
        {
                glm::vec3{-1.0f, 1.0f,-1.0f},
                glm::vec3{-1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        //right
        {
                glm::vec3{1.0f,-1.0f, 1.0f},
                glm::vec3{1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 1.0f}
        },
        {
                glm::vec3{1.0f,-1.0f,-1.0f},
                glm::vec3{1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 0.0f}
        },
        {
                glm::vec3{1.0f, 1.0f,-1.0f},
                glm::vec3{1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 0.0f}
        },
        {
                glm::vec3{1.0f,-1.0f, 1.0f},
                glm::vec3{1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{1.0f, 1.0f}
        },
        {
                glm::vec3{1.0f, 1.0f,-1.0f},
                glm::vec3{1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 0.0f}
        },
        {
                glm::vec3{1.0f, 1.0f, 1.0f},
                glm::vec3{1.0f,0.0f,0.0f},
                glm::vec3{0.0f,0.0f,0.0f},
                glm::vec2{0.0f, 1.0f}
        }
        }
        ){

    }
    ~Cube(){

    }
};
}
#endif





