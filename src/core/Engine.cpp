#include "Engine.h"
#include "scenes/LabScene.h"
#include "scenes/EditorScene.h"
#include "scenes/WaveSurfaceScene.h"
#include "renderer/Renderer.h"
#include "components/Components.h"
#include "scenes/GPUParticlesScene.h"
#include "scenes/game/GameScene.h"


namespace DEngine{
    SceneManager Engine::sceneManager;
    EntitySystemManager Engine::entitySystemManager;
    bool Engine::isRunning;
    Engine::Engine() {
        WindowData testData{"EngineOpenGL", 1600,900};
        window  = std::make_shared<Window>(testData);
        isRunning = true;
        window->setEventCallback(BIND_EVENT_FUNCTION(Engine::input));
        LogManager::init();

        //ECS

        entitySystemManager.registerComponent<TagComponent>();
        entitySystemManager.registerComponent<TransformComponent>();
        entitySystemManager.registerComponent<GravityComponent>();
        entitySystemManager.registerComponent<RigidBodyComponent>();
        //PARTICLES COMPONENTS BEGIN
        entitySystemManager.registerComponent<ParticleComponent>();
        entitySystemManager.registerComponent<ParticlePropertiesComponent>();
        //PARTICLES COMPONENTS END
        entitySystemManager.registerComponent<MeshComponent>();

        auto physicsSystem= entitySystemManager.registerSystem<PhysicsSystem>();
        {
            ComponentsSignature signature;
            //signature.set(entitySystemManager.getComponentType<TagComponent>());
            signature.set(entitySystemManager.getComponentType<TransformComponent>());
            signature.set(entitySystemManager.getComponentType<GravityComponent>());
            signature.set(entitySystemManager.getComponentType<RigidBodyComponent>());
            entitySystemManager.setSystemSignature<PhysicsSystem>(signature);
        }
        auto particleSystem = entitySystemManager.registerSystem<ParticleSystem>();
        {
            ComponentsSignature signature;
            //signature.set(entitySystemManager.getComponentType<TagComponent>());

            signature.set(entitySystemManager.getComponentType<TransformComponent>());
            signature.set(entitySystemManager.getComponentType<ParticleComponent>());
            signature.set(entitySystemManager.getComponentType<ParticlePropertiesComponent>());
            entitySystemManager.setSystemSignature<ParticleSystem>(signature);
        }
        //ECS
        //SCENE PUSHING


        sceneManager.pushScene(new GameScene("BombingSimulator", window));
        //sceneManager.pushScene(new LabScene("Laboratoria", window));
        //sceneManager.pushScene(new WaveSurfaceScene("Waves", window));
        //sceneManager.pushScene(new GPUParticlesScene("RainParticles", window));

        editorScenePtr =  new EditorScene(window);
        sceneManager.pushSceneOverlay(editorScenePtr);
        //SCENE PUSHING
        Renderer::getInstance()->init();

    }
    Engine::~Engine() {
        Renderer::getInstance()->shutdown();
    }
    void Engine::run() {
        static int i=0;
        while(isRunning){
            auto currentFrameTime = static_cast<float>(glfwGetTime());
            deltaTime = currentFrameTime - lastFrameTime;
            lastFrameTime = currentFrameTime;

            editorScenePtr->beginGUI();
            for (Scene* it: sceneManager) {
                it->update(deltaTime);
                i++;

            }
            i=0;
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
        Engine::isRunning = false;
        return true;
    }
}