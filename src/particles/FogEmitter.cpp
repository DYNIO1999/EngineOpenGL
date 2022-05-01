#include "FogEmitter.h"
#include "core/Random.h"
namespace DEngine{

    void FogEmitter::init() {
        totalParticles = numberOfParticles.x;

        uint posBuf;
        uint velBuf;
        uint startBuf;

        std::vector<float> initialPositions;
        std::vector<float> initialVelocities;
        std::vector<float> startPositions;
        glGenBuffers(1, &posBuf);
        glGenBuffers(1, &velBuf);
        glGenBuffers(1, &startBuf);

        glm::vec4 p(0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 transf = glm::translate(glm::mat4(1.0f), glm::vec3(-1,-1,-1));
        for( int i = 0; i < totalParticles; ++i ) {
            p.x = Random::randomFloat(0,50)-50.0f;
            p.y = Random::randomFloat(0,50)-50.0f;
            p.z = Random::randomFloat(0,50)-50.0f;
            p.w = 1.0f;
            p = transf * p;
            initialPositions.push_back(p.x);
            initialPositions.push_back(p.y);
            initialPositions.push_back(p.z);
            initialPositions.push_back(p.w);
        }
        float velocity,theta, phi;
        for( int i = 0; i < totalParticles; ++i) {
            theta = glm::mix(0.0f, glm::pi<float>() / 2.0f, Random::randomFloat(0.0f, 1.0f));
            phi = glm::mix(0.0f, glm::two_pi<float>(), Random::randomFloat(0.0f, 1.0f));

            p.x =sinf(theta) * cosf(phi);
            p.y =cosf(theta);
            p.z = sinf(theta) * sinf(phi);
            p.w = 0;

            velocity = glm::mix(1.25f, 1.5f, Random::randomFloat(0.0f, 10.0f));
            p = glm::normalize(p) * velocity;
            initialVelocities.push_back(p.x);
            initialVelocities.push_back(p.y);
            initialVelocities.push_back(p.z);
            initialVelocities.push_back(p.w);
        }
        startPositions = initialPositions;

        uint bufSize = totalParticles * 4 * sizeof(float);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, posBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initialPositions[0], GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initialVelocities[0], GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, velBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &startPositions[0], GL_DYNAMIC_DRAW);


        glGenVertexArrays(1, &particlesVao);
        glBindVertexArray(particlesVao);
        glBindBuffer(GL_ARRAY_BUFFER, posBuf);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);
    }

    void FogEmitter::update(Shader &_computeShader, float dt) {
        _computeShader.bind();
        _computeShader.setUniform1f("u_DeltaTime", dt);
        glDispatchCompute(totalParticles, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
        _computeShader.unbind();
    }

    void FogEmitter::emit(Shader &_particleShader, const glm::mat4 &_projection, const glm::mat4 &_view,
                            const glm::mat4 &_model) {
        glDepthMask(GL_FALSE);

        _particleShader.bind();
        _particleShader.setUniform1i("u_Texture",0);
        _particleShader.setUniformMat4f("u_Projection",_projection);
        _particleShader.setUniformMat4f("u_View",_view);
        _particleShader.setUniformMat4f("u_Model",_model);
        DENGINE_INFO("SIZE: {}",particleProps.size);
        _particleShader.setUniformVec2f("u_Size",glm::vec2{particleProps.size,particleProps.size});

        glBindVertexArray(particlesVao);
        glDrawArrays(GL_POINTS,0, totalParticles);
        glDepthMask(GL_TRUE);
    }

    void FogEmitter::setProperties(const ParticleProps &_particleProps) {
        particleProps = _particleProps;
    }

}