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

        void pushSceneOverlay(Scene *_overlay);
        void popSceneOverlay(Scene *_overlay);
        void popOverlay();

        void disableScene(Scene* _scene);
        void disableScene(std::string _name);

        std::vector<Scene*>::iterator begin(){return scenesStack.begin();}
        std::vector<Scene*>::iterator end(){return scenesStack.end();}

    private:
        std::vector<Scene*> scenesStack;
        unsigned int sceneIndex=0;
    };
}
#endif