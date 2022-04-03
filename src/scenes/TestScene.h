#ifndef DENGINE_TESTSCENE_H
#define DENGINE_TESTSCENE_H

#include "core/Scene.h"
namespace DEngine {
    class TestScene : public Scene {
    public:
        TestScene(std::string name): Scene(name){

        };

        void input(Event& e) override;
        void update() override;
        int counter = 0;
    };
}
#endif