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
        popScene();
        pushScene(_scene);
    }

    void SceneManager::popChosenScene(Scene *_scene) {
        auto it = std::find(scenesStack.begin(),scenesStack.begin()+sceneIndex,_scene);
        if(it!=scenesStack.begin()+ sceneIndex){
            (*it)->detach();
            delete(*it);
            scenesStack.erase(it);
            sceneIndex--;
        }
    }
    void SceneManager::popScene() {
        auto toDeleteLast = scenesStack.begin()+ (sceneIndex-1);
        (*toDeleteLast)->detach();
        delete (*toDeleteLast);
        scenesStack.erase(toDeleteLast);
        sceneIndex--;
    }

    void SceneManager::pushScene(Scene *_scene) {
        _scene->attach();
        scenesStack.emplace(scenesStack.begin()+sceneIndex, _scene);
        sceneIndex++;
    }

    void SceneManager::pushSceneOverlay(Scene *_overlay) {
        _overlay->attach();
        scenesStack.emplace_back(_overlay);

    }

    void SceneManager::popSceneOverlay(Scene *_overlay) {
        auto it = std::find(scenesStack.begin()+sceneIndex,scenesStack.end(),_overlay);
        if(it!=scenesStack.end()){
            (*it)->detach();
            delete(*it);
            scenesStack.erase(it);
        }
    }

    void SceneManager::disableScene(Scene *_scene) {
        auto it = std::find(scenesStack.begin(),scenesStack.end(),_scene);
        if(it!=scenesStack.end()){
            (*it)->isDisabled=true;
        }
    }

    void SceneManager::disableScene(std::string _name) {
        for (auto it = scenesStack.begin(); it < scenesStack.end() ; it++) {
            if((*it)->getSceneName() ==_name){
                (*it)->isDisabled= true;
                break;
            }
        }
    }
}