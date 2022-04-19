#include "PointEmitter.h"
#include "core/Random.h"
namespace DEngine{
    void PointEmitter::init(const ParticleProps &_particleProps) {
        particleProps = _particleProps;
        totalParticles = numberOfParticles.x * numberOfParticles.y *numberOfParticles.z;

        glm::vec4 p(0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 transf = glm::translate(glm::mat4(1.0f), glm::vec3(-1,-1,-1));
        for( int i = 0; i < numberOfParticles.x; i++ ) {
            for( int j = 0; j < numberOfParticles.y; j++ ) {
                for( int k = 0; k < numberOfParticles.z; k++ ) {
                    p.x = Random::randomFloat(-1000,1000);
                    p.y = Random::randomFloat(-100,100);
                    p.z = Random::randomFloat(-1000,1000);
                    p.w = 1.0f;
                    p = transf * p;
                    initialPositions.push_back(p.x);
                    initialPositions.push_back(p.y);
                    initialPositions.push_back(p.z);
                    initialPositions.push_back(p.w);
                }
            }
        }

        for( int i = 0; i < numberOfParticles.x; i++ ) {
            for( int j = 0; j < numberOfParticles.y; j++ ) {
                for( int k = 0; k < numberOfParticles.z; k++ ) {
                    p.x = 0;
                    p.y = 0;
                    p.z = 0;
                    p.w = 0;
                    initialVelocities.push_back(p.x);
                    initialVelocities.push_back(p.y);
                    initialVelocities.push_back(p.z);
                    initialVelocities.push_back(p.w);
                }
            }
        }


        uint bufs[3];
        glGenBuffers(3, bufs);
        uint posBuf = bufs[0];
        uint velBuf = bufs[1];
        uint startPosBuf = bufs[2];

        uint bufSize = totalParticles * 4 * sizeof(float);

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, posBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initialPositions[0], GL_DYNAMIC_DRAW);

        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initialVelocities[0], GL_DYNAMIC_COPY);


        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, startPosBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initialPositions[0], GL_DYNAMIC_DRAW);

        glGenVertexArrays(1, &particlesVao);
        glBindVertexArray(particlesVao);

        glBindBuffer(GL_ARRAY_BUFFER, posBuf);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);

    }

    void PointEmitter::update(Shader& _computeShader) {
        _computeShader.bind();
        glDispatchCompute(totalParticles / 1000, 1, 1);
        glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
    }
    void PointEmitter::emit(Shader& _particleShader, const glm::mat4& _mvp) {
        _particleShader.bind();
        _particleShader.setUniformMat4f("u_MVP", _mvp);
        _particleShader.setUniformVec4f("u_Color", particleProps.color);
        glBindVertexArray(particlesVao);
        glPointSize(particleProps.size);
        glDrawArrays(GL_POINTS,0, totalParticles);
        glBindVertexArray(0);
    }
    void PointEmitter::emit(const ParticleProps &_particleProps) {
        //particleProps =_particleProps;
        //glDispatchCompute(totalParticles / 1000, 1, 1);
        //glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );
        //glBindVertexArray(particlesVao);
        //NOT FINISHED HERERE DONT USE THAT METHOD
    }
}