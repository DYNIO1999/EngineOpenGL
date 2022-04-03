#include "SceneManager.h"


namespace DEngine{

    SceneManager::SceneManager() {

    }
    SceneManager::~SceneManager() {
        for (auto it = scenesStack.begin(); it <scenesStack.end() ; it++) {
            (*it)->detach();
            delete(*it);
        }
    }

    void SceneManager::changeScene(Scene *_scene) {
        scenesStack.back()->detach();
        delete scenesStack.back();
        scenesStack.pop_back();
        scenesStack.push_back(_scene);
    }

    void SceneManager::popChosenScene(Scene *_scene) {
        auto it = std::find(scenesStack.begin(),scenesStack.end(),_scene);
        if(it!=scenesStack.end()){
            (*it)->detach();
            delete(*it);
            scenesStack.erase(it);
        }
    }

    void SceneManager::popScene() {
        scenesStack.back()->detach();
        delete scenesStack.back();
    }

    void SceneManager::pushScene(Scene *_scene) {
        scenesStack.push_back(_scene);
    }
}