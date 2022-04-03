#ifndef DENGINE_SCENEMANAGER_H
#define DENGINE_SCENEMANAGER_H
#include "Scene.h"
namespace DEngine {

    class SceneManager{
    public:
        SceneManager();
        ~SceneManager();
        void changeScene(Scene* _scene);
        void pushScene(Scene* _scene);
        void popChosenScene(Scene* _scene);
        void popScene();

        std::vector<Scene*>::iterator begin(){return scenesStack.begin();}
        std::vector<Scene*>::iterator end(){return scenesStack.end();}

    private:
        std::vector<Scene*> scenesStack;
    };
}
#endif