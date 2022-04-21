#include "GPUParticlesScene.h"

namespace DEngine{
    void GPUParticlesScene::initScene() {
        projection  = glm::perspective(glm::radians(camera.zoom), (float)1600/900, 0.1f, 100.0f);
        view = glm::mat4(1.0f);
        model = glm::mat4(1.0f);


        std::vector<VertexData> myData{
                {glm::vec3(-0.5f, -0.5f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec2(0.0f, 0.0f)
                },
                {glm::vec3(0.5f, -0.5f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec2(1.0f, 0.0f)
                },
                {glm::vec3(0.0f,  0.5f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec3(0.0f, 0.0f, 0.0f),
                        glm::vec2(0.5f, 1.0f)
                }
        };
        std::vector<Index> myIndexData{0, 1, 2,
                                       1, 2, 0};


        std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(myData, myIndexData);
        TransformComponent testTransform;
        testTransform.transform = glm::mat4(1);

        MeshComponent testMesh;
        testMesh.meshes.push_back(mesh);

        entities.emplace_back(Engine::entitySystemManager.createEntity());

    }

    void GPUParticlesScene::input(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(GPUParticlesScene::windowClose));
        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(GPUParticlesScene::onKeyPressedInput));
        dispatcher.dispatch<MouseButtonPressed>(BIND_EVENT_FUNCTION(GPUParticlesScene::onMousePressed));
        dispatcher.dispatch<MouseButtonReleased>(BIND_EVENT_FUNCTION(GPUParticlesScene::onMouseReleased));
        dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(GPUParticlesScene::onMouseMovedEvent));
    }

    void GPUParticlesScene::update(float dt) {

        DrawCallSettings testSettings;
        testSettings.enableBlendingFlag =true;

        view = camera.GetViewMatrix();

        Renderer::getInstance()->clear(glm::vec4(250.0f/255.0f, 125.0f/255.0f, 76.0f/255.0f ,1.0));
        Renderer::getInstance()->beginDraw(projection,testSettings);


        //for (const auto& ent: entities) {
        //    if(Engine::entitySystemManager.hasComponent<MeshComponent>(ent)){
        //        Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(ent), )
        //    }
        //}

        //DRAW HERE
        Renderer::getInstance()->endDraw();
    }
    bool GPUParticlesScene::onKeyPressedInput(KeyPressedEvent& e){
        switch (e.getKeyCode()) {
            case W:
                camera.processKeyboard(Camera_Movement::FORWARD_CAMERA_MOVE, 0.1);
                break;
            case A:
                camera.processKeyboard(Camera_Movement::LEFT_CAMERA_MOVE, 0.1);
                break;
            case S:
                camera.processKeyboard(Camera_Movement::BACKWARD_CAMERA_MOVE, 0.1);
                break;
            case D:
                camera.processKeyboard(Camera_Movement::RIGHT_CAMERA_MOVE, 0.1);
                break;
        }
        return  true;
    }
    bool GPUParticlesScene::onMouseMovedEvent(MouseMovedEvent& e){
        if(isButtonPressed) {
            double mouseX;
            double mouseY;

            mouseX = e.getX();
            mouseY = e.getY();
            float rotX = (float) (mouseY - (static_cast<float>(windowPtr->getHeight() / 2.0f))) /
                         static_cast<float>(windowPtr->getHeight());
            float rotY = (float) (mouseX - (static_cast<float>(windowPtr->getWidth() / 2.0f))) /
                         static_cast<float>(windowPtr->getWidth());

            camera.processMouseMovement(rotX, rotY);
            glfwSetCursorPos(windowPtr->getGLFWWindow(), (static_cast<float>(windowPtr->getWidth() / 2.0f)), (static_cast<float>(windowPtr->getHeight()/ 2.0f)));
        }
        return true;
    }


    bool GPUParticlesScene::onMousePressed(MouseButtonPressed &e) {
        if(e.getMouseCode() ==ButtonLeft){
            isButtonPressed =true;
        }
        if(e.getMouseCode() ==ButtonRight){
            camera.front= glm::vec3(0.0f, 0.0f, -1.0f);
        }
        return true;
    }
    bool GPUParticlesScene::onMouseReleased(MouseButtonReleased& e){
        if(e.getMouseCode() ==ButtonLeft){
            isButtonPressed = false;
        }
        return true;
    }
    bool GPUParticlesScene::windowClose(WindowCloseEvent& e){
        Engine::isRunning = false;
        return true;
    }



}