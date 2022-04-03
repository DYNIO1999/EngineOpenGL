#include "Engine.h"
#include "scenes/TestScene.h"
#include "scenes/EditorScene.h"

namespace DEngine{
    SceneManager Engine::sceneManager;
    Engine::Engine() {
        WindowData testData{"DEngine", 1600,900};
        window  = std::make_shared<Window>(testData);
        isRunning = true;
        window->setEventCallback(BIND_EVENT_FUNCTION(Engine::input));
        LogManager::init();
        sceneManager.pushScene(new TestScene("HELLOOO"));
        editorScenePtr =  new EditorScene(window);
        sceneManager.pushSceneOverlay(editorScenePtr);
    }
    Engine::~Engine() {

    }
    void Engine::run() {

        while(isRunning){

            editorScenePtr->beginGUI();
            for (Scene* it: sceneManager) {
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                glClear(GL_COLOR_BUFFER_BIT);
                it->update();
            }
            editorScenePtr->endGUI();
            window->Update();
        }
    }
    void Engine::input(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Engine::windowClose));
        for (auto it = sceneManager.end(); it != sceneManager.begin();) {
            it--;
            (*it)->input(e);
            if(e.handled){
                break;
            }
        }
    }

    bool Engine::windowClose(WindowCloseEvent &e) {
        isRunning = false;
        return true;
    }
}