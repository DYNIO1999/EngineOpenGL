#include "PhysicsSystem.h"
#include "components/Components.h"
#include <glm/glm.hpp>
#include "glm/ext.hpp"

namespace DEngine{

    void PhysicsSystem::init() {

    }
    void PhysicsSystem::update(float dt) {
        for (auto const& entity: entities) {
            //auto& rigidBodyComp = entitySystemManager.getComponent<RigidBodyComponent>(entity);
            //auto& transformComp =entitySystemManager.getComponent<TransformComponent>(entity);
            //auto& gravityComp = entitySystemManager.getComponent<GravityComponent>(entity);
            //transformComp.transform =glm::translate(transformComp.transform, rigidBodyComp.velocity * dt);
            //rigidBodyComp.velocity += gravityComp.gravityForce*dt;
        }
    }
}