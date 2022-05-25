#include "GameScene.h"
#include "input/Input.h"
#include "core/Engine.h"


namespace DEngine{

    void GameScene::attach(){
        //INITING STUFF
        DENGINE_WARN("HEY GAME SCENE!");
        isButtonPressed = false;
        projection  = glm::perspective(glm::radians(camera.zoom), (float)1600/900, 0.1f, 100.0f);
        glm::vec3 cameraPos(0.0f,0.0f,1.0f);
        view = glm::lookAt(cameraPos,
                           cameraPos+glm::vec3(0.0f, 0.0f, -1.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));

        model = glm::mat4(1.0f);
        playerview = glm::mat4(1.0f);


        //MODEL LOADING
        planeModel = std::make_shared<Model>(PATH_MODELS+"plane/plane.obj",true);
        playerShader =  std::make_shared<Shader>(PATH_SHADERS+ "TestVertexShader.glsl",PATH_SHADERS+ "TestFragmentShader.glsl");

        bombModel = std::make_shared<Model>(PATH_MODELS_GAME+ "bomb.obj");

        //MODEL LOADING

        entities.emplace_back(Engine::entitySystemManager.createEntity()); //0
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //1

        //PLAYER
        TagComponent playerTagComp;
        playerTagComp.tag = "PLAYER";
        Engine::entitySystemManager.addComponent(entities[0],playerTagComp);
        TransformComponent playerTransformComp;
        playerTransformComp.transform = glm::translate(glm::mat4(1), glm::vec3(0.0f,-1.0f,-5.0f));
        //playerTransformComp.transform =  glm::rotate(playerTransformComp.transform,glm::radians(270.f), glm::vec3(0.0f,1.0f,0.0f));
        Engine::entitySystemManager.addComponent(entities[0],playerTransformComp);
        MeshComponent playerMeshComp;
        playerMeshComp.meshes = planeModel->meshes;
        playerMeshComp.textures= planeModel->textures;
        Engine::entitySystemManager.addComponent(entities[0], playerMeshComp);
        //PLAYER

        TransformComponent testCubeTransformComp;
        testCubeTransformComp.transform = glm::mat4(1.0f);
        testCubeTransformComp.transform =  glm::translate(testCubeTransformComp.transform, glm::vec3(0.0f,0.0f,-100.0f));
        Engine::entitySystemManager.addComponent(entities[1],testCubeTransformComp);
        MeshComponent testCubeMeshComp;
        testCubeMeshComp.meshes = bombModel->meshes;
        Engine::entitySystemManager.addComponent(entities[1], testCubeMeshComp);


    }
    void GameScene::input(Event& e){
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(GameScene::windowClose));
        dispatcher.dispatch<MouseButtonPressed>(BIND_EVENT_FUNCTION(GameScene::onMousePressed));
        dispatcher.dispatch<MouseButtonReleased>(BIND_EVENT_FUNCTION(GameScene::onMouseReleased));
        dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(GameScene::onMouseMovedEvent));

        //auto [x,y] = Input::getMousePosition();
        //DENGINE_INFO("X {}  Y {}", x, y);
    }
    void GameScene::update(float dt){


        DENGINE_WARN("{}, {},{}",maxPlaneAngle[0],maxPlaneAngle[1], maxPlaneAngle[2]);
        if(Input::isKeyPressed(GLFW_KEY_W)){
            if(maxPlaneAngle[0]<=(120.0f)) {
                maxPlaneAngle += glm::vec3(1.0f, 0.0f, 0.0f);
                Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform = glm::rotate(
                        Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,
                        glm::radians(0.2f), glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }else if(Input::isKeyPressed(GLFW_KEY_S)){
            if(maxPlaneAngle[0]>=(-120.0f)) {
                maxPlaneAngle += glm::vec3(-1.0f, 0.0f, 0.0f);
                Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform = glm::rotate(
                        Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,
                        glm::radians(-0.2f), glm::vec3(1.0f, 0.0f, 0.0f));
            }
        }else if(Input::isKeyPressed(GLFW_KEY_A)){
                if(maxPlaneAngle[2]<=(120.0f)) {
                    dir =glm::vec3(-1.0f,0.0f,0.0f);
                    maxPlaneAngle += glm::vec3(0.0f, 0.0f, 1.0f);
                    Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform = glm::rotate(
                            Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,
                            glm::radians(0.2f), glm::vec3(0.0f, 0.0f, 1.0f));

            }
        }else if(Input::isKeyPressed(GLFW_KEY_D)){
                if(maxPlaneAngle[2]>=(-120.0f)) {
                    dir =glm::vec3(1.0f,0.0f,0.0f);
                    maxPlaneAngle += glm::vec3(0.0f, 0.0f, -1.0f);
                    Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform = glm::rotate(
                            Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,
                            glm::radians(-0.2f), glm::vec3(0.0f, 0.0f, 1.0f));
                }
        }
        DENGINE_ERROR("{},{},{}", camera.position[0],camera.position[1], camera.position[2]);
        currentDeltaTime = dt;

        DENGINE_ERROR("SPEEED {}", dir[0]*dt);
        Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform =
                glm::translate( Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform, glm::vec3(dir[0]*dt,0.0f,-10.0f*dt));


        glm::vec3 cameraPos = glm::vec3(Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform[3])+glm::vec3(0.0f,1.0f,5.0f);
        glm::vec3 cameraTarget =glm::vec3(Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform[3]);
        playerview = camera.Get3RDPersonViewMatrix(cameraPos, cameraTarget);


        DrawCallSettings  testSettings;
        testSettings.enableBlendingFlag=true;
        testSettings.enableDepthTestFlag=true;
        Renderer::getInstance()->clear(glm::vec4(0.862, 0.984, 0.996, 1.0));
        Renderer::getInstance()->beginDraw(glm::mat4(1), testSettings);

        playerShader->bind();
        playerShader->setUniformMat4f("projection", projection);

        playerShader->setUniformMat4f("view",playerview);
        //playerShader->setUniformMat4f("model", glm::translate(glm::translate(glm::mat4(1), glm::vec3(0.0f,-1.0f,-7.0f)), camera.position));
        playerShader->setUniformMat4f("model",glm::translate(  Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,camera.position));
        Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[0]), *playerShader);



        playerShader->bind();
        playerShader->setUniformMat4f("projection", projection);
        playerShader->setUniformMat4f("view", playerview);
        playerShader->setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[1]).transform);
        Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[1]), *playerShader);

        Renderer::getInstance()->endDraw();
        //POP SCENE IN PROPER WAY DONT REMOVE!
        //if(timeCounter>5){
        //    Renderer::getInstance()->clear();
        //    Engine::sceneManager.popScene();
        //    return;
        //}
    }


    void GameScene::detach(){
        //DELETING STUFF
        for(auto it = entities.begin();it<entities.end();it++){
            Engine::entitySystemManager.destroyEntity(*it);
        }
    }

    bool GameScene::onKeyPressedInput(KeyPressedEvent& e){
        return true;
    }
    bool GameScene::windowClose(WindowCloseEvent& e){
        Engine::isRunning = false;
        return true;
    }
    bool GameScene::onMousePressed(MouseButtonPressed& e){
        if(e.getMouseCode() ==ButtonRight){
            if(isButtonPressed){
                isButtonPressed =false;
            }else{
                isButtonPressed =true;
            }
        }
        return true;
    }
    bool GameScene::onMouseReleased(MouseButtonReleased& e){
        return true;
    }
    bool GameScene::onMouseMovedEvent(MouseMovedEvent& e){
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
}