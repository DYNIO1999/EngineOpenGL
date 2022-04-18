#ifndef DENGINE_RANDOM_H
#define DENGINE_RANDOM_H
#include <random>

namespace DEngine{
    class Random{
    public:
        static void init(){
            generator.seed(std::random_device()());
        }
        template<typename T>
        static T generateRandom();
        template <>
        static float generateRandom<float>(){
            return  distribution(generator);
        }
        template <>
        static int generateRandom<int>(){
            return  static_cast<int>(distribution(generator));
        }
    private:
        static std::mt19937 generator;
        static std::uniform_real_distribution<float> distribution;
    };
}
#endif