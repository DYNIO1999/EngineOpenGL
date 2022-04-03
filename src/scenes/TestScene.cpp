#include "TestScene.h"
#include "core/LogManager.h"
#include "core/Engine.h"

namespace DEngine{

    void TestScene::input(Event &e) {
        //std::cout<<e.getName()<<'\n';
    }
    void TestScene::update() {
        DENGINE_TRACE("SCENE IS UPDATING: {} ", getSceneName());
        if(counter==0){
            Engine::sceneManager.changeScene(new TestScene("Second"));
            counter++;
        }
    }
}