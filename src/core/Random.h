#ifndef DENGINE_RANDOM_H
#define DENGINE_RANDOM_H
#include <random>

namespace DEngine{
    class Random{
    public:
        static void init(){
            random.seed(std::random_device()());
        }
        template<typename T>
        static T generateRandom();
        template <>
        static float generateRandom<float>(){
            return  ((float)distribution(random))/ ((float)std::numeric_limits<int>::max());
        }
        template <>
        static int generateRandom<int>(){
            return  ((int)distribution(random));
        }

    private:
        static std::mt19937 random;
        static std::uniform_int_distribution<std::mt19937::result_type> distribution;
    };
}
#endif