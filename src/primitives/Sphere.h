#ifndef DENGINE_SPHERE_H
#define DENGINE_SPHERE_H
#include "renderer/Mesh.h"


namespace DEngine{
    class Sphere:public Mesh
    {
    public:
        Sphere(float _radius, uint _slices, GLuint _stacks):
        radius(_radius),
        slices(_slices),
        stacks(_stacks)
        {
            
            //initMesh();
        }
        ~Sphere(){

        }
        float getRadius(){return  radius;}
    private:
        void init(){
            int nVerts = (slices + 1) * (stacks + 1);
            int elements = (slices * 2 * (stacks - 1)) * 3;


            
            // Verts
            //std::vector<GLfloat> p(3 * nVerts);
            //// Normals
            //std::vector<GLfloat> n(3 * nVerts);
            //// Tex coords
            //std::vector<GLfloat> tex(2 * nVerts);
            //// Elements
            //std::vector<GLuint> el(elements);
        }

        float radius;
        uint slices;
        uint stacks;
    };        
}
#endif
