#ifndef DENGINE_PARTICLE_H
#define DENGINE_PARTICLE_H
#include <glm/glm.hpp>


namespace  DEngine {
  struct Particle {
      Particle():
      position(glm::vec3(0.0f,0.0f,0.0f)),
      lifeTime(1.0f)
      {

      }
      Particle(const glm::vec3 &_position, float _lifeTime) :
              position(_position),
              lifeTime(_lifeTime) {
      }
      ~Particle() =default;
      glm::vec3 position;
      float lifeTime;
    };
}
#endif