#ifndef DENGINE_SPHERE_H
#define DENGINE_SPHERE_H
#include "renderer/Mesh.h"



/*
 // Verts
    std::vector<GLfloat> p(3 * nVerts);
    // Normals
    std::vector<GLfloat> n(3 * nVerts);
    // Tex coords
    std::vector<GLfloat> tex(2 * nVerts);
    // Elements
    std::vector<GLuint> el(elements);

	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / nSlices;
	GLfloat phiFac = glm::pi<float>() / nStacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for( GLuint i = 0; i <= nSlices; i++ ) {
		theta = i * thetaFac;
                s = (GLfloat)i / nSlices;
		for( GLuint j = 0; j <= nStacks; j++ ) {
			phi = j * phiFac;
                        t = (GLfloat)j / nStacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			p[idx] = radius * nx; p[idx+1] = radius * ny; p[idx+2] = radius * nz;
			n[idx] = nx; n[idx+1] = ny; n[idx+2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx+1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for( GLuint i = 0; i < nSlices; i++ ) {
		GLuint stackStart = i * (nStacks + 1);
		GLuint nextStackStart = (i+1) * (nStacks+1);
		for( GLuint j = 0; j < nStacks; j++ ) {
			if( j == 0 ) {
				el[idx] = stackStart;
				el[idx+1] = stackStart + 1;
				el[idx+2] = nextStackStart + 1;
				idx += 3;
			} else if( j == nStacks - 1) {
				el[idx] = stackStart + j;
				el[idx+1] = stackStart + j + 1;
				el[idx+2] = nextStackStart + j;
				idx += 3;
			} else {
				el[idx] = stackStart + j;
				el[idx+1] = stackStart + j + 1;
				el[idx+2] = nextStackStart + j + 1;
				el[idx+3] = nextStackStart + j;
				el[idx+4] = stackStart + j;
				el[idx+5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}

 */
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
            int numberOfVertex = (slices + 1) * (stacks + 1);
            int numberOfIndexes = (slices * 2 * (stacks - 1)) * 3;
            
            // Verts
            std::vector<float> vertices(3 * numberOfVertex);
            //// Normals
            std::vector<float> normals(3 * numberOfVertex);
            //// Tex coords
            std::vector<float> texturs(2 * numberOfVertex);
            //// Elements
            std::vector<uint> indices(numberOfIndexes);


            // Generate positions and normals
            float theta, phi;
            float thetaFac = glm::two_pi<float>() / slices;
            float phiFac = glm::pi<float>() / stacks;
            float nx, ny, nz, s, t;
            uint idx = 0, tIdx = 0;
            for( GLuint i = 0; i <= slices; i++ ) {
                theta = i * thetaFac;
                s = (float)i / slices;
                for( uint j = 0; j <= stacks; j++ ) {
                    phi = j * phiFac;
                    t = (float )j / stacks;
                    nx = sinf(phi) * cosf(theta);
                    ny = sinf(phi) * sinf(theta);
                    nz = cosf(phi);
                    vertices[idx] = radius * nx; vertices[idx+1] = radius * ny; vertices[idx+2] = radius * nz;
                    normals[idx] = nx; normals[idx+1] = ny; normals[idx+2] = nz;
                    idx += 3;
                    texturs[tIdx] = s;
                    texturs[tIdx+1] = t;
                    tIdx += 2;
                }
            }

            idx = 0;
            for(uint i = 0; i < slices; i++ ) {
                uint stackStart = i * (stacks + 1);
                uint nextStackStart = (i + 1) * (stacks + 1);
                for (uint j = 0; j < stacks; j++) {
                    if (j == 0) {
                        indices[idx] = stackStart;
                        indices[idx + 1] = stackStart + 1;
                        indices[idx + 2] = nextStackStart + 1;
                        idx += 3;
                    } else if (j == stacks - 1) {
                        indices[idx] = stackStart + j;
                        indices[idx + 1] = stackStart + j + 1;
                        indices[idx + 2] = nextStackStart + j;
                        idx += 3;
                    } else {
                        indices[idx] = stackStart + j;
                        indices[idx + 1] = stackStart + j + 1;
                        indices[idx + 2] = nextStackStart + j + 1;
                        indices[idx + 3] = nextStackStart + j;
                        indices[idx + 4] = stackStart + j;
                        indices[idx + 5] = nextStackStart + j + 1;
                        idx += 6;
                    }
                }
            }

            //std::vector<VertexData> data;
            //data.resize(numberOfVertex);
            //for(int i=0;i<numberOfVertex;i++){
            //    VertexData temp;
            //    temp.position =
            //}



        }
        float radius;
        uint slices;
        uint stacks;
    };        
}
#endif
