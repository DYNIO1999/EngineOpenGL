#include "GPUParticlesScene.h"
#include "particles/RainEmitter.h"
#include "primitives/Cube.h"
namespace DEngine{
    void GPUParticlesScene::initScene() {
        projection  = glm::perspective(glm::radians(camera.zoom), (float)1600/900, 0.1f, 100.0f);
        view = glm::mat4(1.0f);
        model = glm::mat4(1.0f);




        entities.emplace_back(Engine::entitySystemManager.createEntity());
        entities.emplace_back(Engine::entitySystemManager.createEntity());
        TransformComponent testTransformComponent;
        testTransformComponent.transform = glm::mat4(1);
        Engine::entitySystemManager.addComponent(entities[0], testTransformComponent);

        std::shared_ptr<Shader> computeShader = std::make_shared<Shader>(PATH_SHADERS + "particles/rain/RainComputeShader.glsl");
        std::shared_ptr<Shader> rainParticleShader = std::make_shared<Shader>(PATH_SHADERS + "particles/rain/RainVertexShader.glsl",
                                                                              PATH_SHADERS + "particles/rain/RainGeometryShader.glsl",
                                                                              PATH_SHADERS + "particles/rain/RainFragmentShader.glsl");

        ParticleProps testParticleProperties;

        testParticleProperties.color= glm::vec4(0.549, 0.768, 0.933, 1.0f);
        testParticleProperties.size=0.1f;

        ParticleComponent testParticleComponent;
        testParticleComponent.particleProps = testParticleProperties;
        testParticleComponent.emitter = std::make_shared<RainEmitter>(glm::ivec3(100,100,100));
        testParticleComponent.computeShader = computeShader;
        testParticleComponent.particleShader = rainParticleShader;

        Engine::entitySystemManager.addComponent(entities[0], testParticleComponent);

        TransformComponent testObjTransform;
        testObjTransform.transform  = glm::mat4(1);
        testObjTransform.transform =  glm::scale(testObjTransform.transform, glm::vec3(10.0f,5.0f,10.0f));
        Engine::entitySystemManager.addComponent(entities[1], testObjTransform);
        Cube testCubeMesh;


        MeshComponent testObjMeshComponent;
        testObjMeshComponent.mesh.push_back(testCubeMesh);
        Engine::entitySystemManager.addComponent(entities[1], testObjMeshComponent);




        float skyboxVertices[] = {
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
        vertexBufferSkybox = std::make_shared<VertexBuffer>(skyboxVertices, sizeof(skyboxVertices),sizeof(skyboxVertices)/sizeof(float));
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
        currentDeltaTime =dt;
        DrawCallSettings testSettings;
        testSettings.enableBlendingFlag =true;
        testSettings.enableDepthTestFlag =true;

        view = camera.GetViewMatrix();
        glm::mat4 secondView = glm::mat4(glm::mat3(camera.GetViewMatrix()));

        Renderer::getInstance()->clear(glm::vec4(0.0f,0.0f,0.0f,0.0f));
        Renderer::getInstance()->beginDraw(projection,testSettings);



        basicShader.bind();
        brickTexture.bind(0);
        basicShader.setUniform1i("u_Texture",0);
        for (const auto& ent: entities) {
            if(Engine::entitySystemManager.hasComponent<MeshComponent>(ent)){
                basicShader.setUniformMat4f("projection",projection);
                basicShader.setUniformMat4f("view",view);
                basicShader.setUniformMat4f("model",Engine::entitySystemManager.getComponent<TransformComponent>(ent).transform);
                Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(ent).mesh.at(0), basicShader);
            }
        }
        basicShader.unbind();
        brickTexture.unbind();




        glDepthFunc(GL_LEQUAL);
        skyBoxShader.bind();
        cubeMap.bind(1);
        skyBoxShader.setUniform1i("u_Skybox", 1);
        skyBoxShader.setUniformMat4f("projection", projection);
        skyBoxShader.setUniformMat4f("view", secondView);
        Renderer::getInstance()->draw(*vertexArraySkybox, skyBoxShader);
        cubeMap.unbind();
        skyBoxShader.unbind();
        glDepthFunc(GL_LESS);

        Engine::entitySystemManager.getSystem<ParticleSystem>()->update(dt, projection, view, model);



        Renderer::getInstance()->endDraw();
    }
    bool GPUParticlesScene::onKeyPressedInput(KeyPressedEvent& e){
        switch (e.getKeyCode()) {
            case W:
                camera.processKeyboard(Camera_Movement::FORWARD_CAMERA_MOVE, 25* currentDeltaTime);
                break;
            case A:
                camera.processKeyboard(Camera_Movement::LEFT_CAMERA_MOVE, 25* currentDeltaTime);
                break;
            case S:
                camera.processKeyboard(Camera_Movement::BACKWARD_CAMERA_MOVE, 25* currentDeltaTime);
                break;
            case D:
                camera.processKeyboard(Camera_Movement::RIGHT_CAMERA_MOVE, 25* currentDeltaTime);
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