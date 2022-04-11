#ifndef DENGINE_SYSTEM_H
#define DENGINE_SYSTEM_H
#include <set>
#include "Entity.h"
namespace  DEngine {
    class System {
    public:
        std::set<Entity> entities;
    };
}
#endif