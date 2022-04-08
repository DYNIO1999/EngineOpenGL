#ifndef DENGINE_COMPONENT_H
#define DENGINE_COMPONENT_H

#include <cstdint>
#include <bitset>

using ComponentType = std::uint8_t;
const ComponentType MAX_COMPONENTS = 32;
using ComponentsSignature = std::bitset<MAX_COMPONENTS>;

#endif
