#include "GPUParticlesScene.h"
#include "particles/RainEmitter.h"

namespace DEngine{
    void GPUParticlesScene::initScene() {
        projection  = glm::perspective(glm::radians(camera.zoom), (float)1600/900, 0.1f, 100.0f);
        view = glm::mat4(1.0f);
        model = glm::mat4(1.0f);




        entities.emplace_back(Engine::entitySystemManager.createEntity());
        TransformComponent testTransformComponent;
        testTransformComponent.transform = glm::mat4(1);
        Engine::entitySystemManager.addComponent(entities[0], testTransformComponent);

        std::shared_ptr<Shader> computeShader = std::make_shared<Shader>(PATH_SHADERS + "particles/rain/RainComputeShader.glsl");
        std::shared_ptr<Shader> rainParticleShader = std::make_shared<Shader>(PATH_SHADERS + "particles/rain/RainVertexShader.glsl",
                                                                              PATH_SHADERS + "particles/rain/RainGeometryShader.glsl",
                                                                              PATH_SHADERS + "particles/rain/RainFragmentShader.glsl");

        ParticleProps testParticleProperties;
        testParticleProperties.color= glm::vec4(0.356, 0.737, 0.862, 1.0f);
        testParticleProperties.size=0.09f;

        ParticleComponent testParticleComponent;
        testParticleComponent.particleProps = testParticleProperties;
        testParticleComponent.emitter = std::make_shared<RainEmitter>(glm::ivec3(100,100,100));
        testParticleComponent.computeShader = computeShader;
        testParticleComponent.particleShader = rainParticleShader;

        Engine::entitySystemManager.addComponent(entities[0], testParticleComponent);






        float cubeVertices[] = {
                // positions          // texture Coords
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
                0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
                0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
                -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
                -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };
        float skyboxVertices[] = {
                // positions
                -1.0f,  1.0f, -1.0f,
                -1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f, -1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,

                -1.0f, -1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f, -1.0f,  1.0f,
                -1.0f, -1.0f,  1.0f,

                -1.0f,  1.0f, -1.0f,
                1.0f,  1.0f, -1.0f,
                1.0f,  1.0f,  1.0f,
                1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f,  1.0f,
                -1.0f,  1.0f, -1.0f,

                -1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f, -1.0f,
                1.0f, -1.0f, -1.0f,
                -1.0f, -1.0f,  1.0f,
                1.0f, -1.0f,  1.0f
        };



        vertexBufferCube = std::make_shared<VertexBuffer>(cubeVertices, sizeof(cubeVertices)/sizeof(float));
        vertexBufferLayoutCube = std::make_shared<VertexBufferLayout>();
        vertexBufferLayoutCube->push<float>(3);
        vertexBufferLayoutCube->push<float>(2);
        vertexArrayCube = std::make_shared<VertexArray>();
        vertexArrayCube->addBuffer(*vertexBufferCube, *vertexBufferLayoutCube);

        vertexBufferSkybox = std::make_shared<VertexBuffer>(skyboxVertices, sizeof(skyboxVertices)/sizeof(float));
        vertexBufferLayoutSkybox = std::make_shared<VertexBufferLayout>();
        vertexBufferLayoutSkybox->push<float>(3);
        vertexArraySkybox = std::make_shared<VertexArray>();
        vertexArraySkybox->addBuffer(*vertexBufferSkybox, *vertexBufferLayoutSkybox);

        initSystems();
    }
    void GPUParticlesScene::initSystems() {
        Engine::entitySystemManager.getSystem<ParticleSystem>()->init();
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
        testSettings.enableBlendingFlag =false;

        view = camera.GetViewMatrix();

        Renderer::getInstance()->clear(glm::vec4(0,0,0,1.0));
        Renderer::getInstance()->beginDraw(projection,testSettings);

        for (const auto& ent: entities) {
            if(Engine::entitySystemManager.hasComponent<MeshComponent>(ent)){
                //Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(ent), )
            }
        }
        //DRAW HERE
        Renderer::getInstance()->endDraw();
        Engine::entitySystemManager.getSystem<ParticleSystem>()->update(dt, projection, view, model);

        //Renderer::getInstance()->beginDraw(projection,testSettings);
        //Renderer::getInstance()->endDraw();

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