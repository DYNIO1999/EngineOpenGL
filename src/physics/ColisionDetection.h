#ifndef DENGINE_COLISIONDETECTION_H
#define DENGINE_COLISIONDETECTION_H
#include <cmath>
#include "components/Components.h"
namespace DEngine {
    class ColisionDetection {
    public:
        static bool collideAABBtoAABB(const BoxCollider& _colliderA,const BoxCollider& _colliderB){
            if((std::abs(_colliderA.center.x - _colliderB.center.x)) > (_colliderA.extents.x + _colliderB.extents.x)){
                return false;
            }
            if((std::abs(_colliderA.center.y - _colliderB.center.y)) > (_colliderA.extents.y + _colliderB.extents.y)){
                return false;
            }
            if((std::abs(_colliderA.center.z - _colliderB.center.z)) > (_colliderA.extents.z + _colliderB.extents.z)){
                return false;
            }
            return true;
        }
    private:
        ColisionDetection(){

    }
    ~ColisionDetection(){

    }
    };
}
#endif
