#include "LabScene.h"
#include "core/LogManager.h"
#include "core/Engine.h"

#include "core/Random.h"
#include "components/Components.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "particles/PointEmitter.h"
#include "particles/SmokeEmitter.h"
#include "particles/FogEmitter.h"
#include "primitives/Cube.h"

namespace DEngine{

    static void transformEditorDraw(){
        float col[3]{0,0,0};
        ImGui::Begin("Editor");
        if (ImGui::CollapsingHeader("Position"))
        {
            ImGui::InputFloat3("Position", col);
        }
        if (ImGui::CollapsingHeader("Rotation"))
        {
            ImGui::InputFloat3("Rotation", col);
        }
        if (ImGui::CollapsingHeader("Color"))
        {
            ImGui::ColorPicker3("Color",col, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
        }
        ImGui::End();
    }
    LabScene::~LabScene(){
    }
    void LabScene::detach() {
            for(auto it = entities.begin();it<entities.end();it++){

                std::cout<<*it<<' ';

                Engine::entitySystemManager.destroyEntity(*it);

            }
            std::cout<<'\n';
    }

    void LabScene::initData() {
        projection  = glm::perspective(glm::radians(camera.zoom), (float)1600/900, 0.1f, 100.0f);


        glm::vec3 cameraPos(0.0f,0.0f,1.0f);
        view = glm::lookAt(cameraPos,
                           cameraPos+glm::vec3(0.0f, 0.0f, -1.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));

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

       // testMesh = std::make_shared<Mesh>(myData, myIndexData);
        //testMesh = std::make_shared<Mesh>(myData);

        //testModel = std::make_shared<Model>(PATH_MODELS+"sword/scene.gltf");
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //0
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //1
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //2


        //CUBES
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //3
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //4
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //5
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //6
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //7
        //CUBES END


        //LIGHTNING CUBES
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //8
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //9
        //LIGHTNING CUBES

        TransformComponent testComp;
        testComp.transform = glm::mat4(1.0f);

        ///SMOKE PARTICLES BEGIN
        std::shared_ptr<Shader> smokeComputeShader;
        std::shared_ptr<Shader> smokeParticleShader;

        std::shared_ptr<Shader> fogComputeShader;
        std::shared_ptr<Shader> fogParticleShader;


        fogComputeShader  = std::make_shared<Shader>(PATH_SHADERS + "particles/fog/FogComputeShader.glsl");
        fogParticleShader = std::make_shared<Shader>(PATH_SHADERS + "particles/fog/FogVertexShader.glsl",
                                                       PATH_SHADERS +"particles/fog/FogGeometryShader.glsl",
                                                       PATH_SHADERS + "particles/fog/FogFragmentShader.glsl");


        DENGINE_ERROR("FOG PARTICLE SHADER->{}", fogParticleShader->getHandle());

        smokeComputeShader = std::make_shared<Shader>(PATH_SHADERS + "particles/smoke/SmokeComputeShader.glsl");
        smokeParticleShader = std::make_shared<Shader>(PATH_SHADERS + "particles/smoke/SmokeVertexShader.glsl",
                                                     PATH_SHADERS +"particles/smoke/SmokeGeometryShader.glsl",
                                                     PATH_SHADERS + "particles/smoke/SmokeFragmentShader.glsl");


        DENGINE_ERROR("SMOKE PARTICLE SHADER->{}", smokeParticleShader->getHandle());
        DENGINE_ERROR("STANDARD  SHADER->{}",testShader.getHandle());
        std::shared_ptr<Texture> particleTexture = std::make_shared<Texture>(PATH_TEXTURES+"smoke.png");

        testComp.transform = glm::mat4(1.0f);

        ParticlePropertiesComponent particlePropertiesComponent1;
        particlePropertiesComponent1.particleProps;
        particlePropertiesComponent1.particleProps.size =10.0f;
        ParticleComponent particleComponent;
        particleComponent.emitter = std::make_shared<FogEmitter>(1000);
        particleComponent.particleShader = fogParticleShader;
        particleComponent.computeShader = fogComputeShader;
        particleComponent.texture =particleTexture;

        Engine::entitySystemManager.addComponent(entities[0],testComp);
        Engine::entitySystemManager.addComponent(entities[0], particleComponent);
        Engine::entitySystemManager.addComponent(entities[0], particlePropertiesComponent1);

        testComp.transform = glm::mat4(1.0f);
        testComp.transform = glm::translate(testComp.transform, glm::vec3(-10.0f,0.0f,0.0f));
        ParticlePropertiesComponent particlePropertiesComponent2;
        particlePropertiesComponent2.particleProps.size =5.0f;
        ParticleComponent particleComponent2;
        particleComponent2.emitter = std::make_shared<SmokeEmitter>(1000);
        particleComponent2.particleShader = smokeParticleShader;
        particleComponent2.computeShader = smokeComputeShader;
        particleComponent2.texture =particleTexture;

        Engine::entitySystemManager.addComponent(entities[1],testComp);
        Engine::entitySystemManager.addComponent(entities[1], particleComponent2);
        Engine::entitySystemManager.addComponent(entities[1], particlePropertiesComponent2);


        testComp.transform = glm::mat4(1.0f);
        testComp.transform = glm::translate(testComp.transform, glm::vec3(10.0f,0.0f,0.0f));
        ParticlePropertiesComponent particlePropertiesComponent3;
        particlePropertiesComponent3.particleProps.size =5.0f;

        Engine::entitySystemManager.addComponent(entities[2],testComp);
        Engine::entitySystemManager.addComponent(entities[2], particleComponent2);
        Engine::entitySystemManager.addComponent(entities[2], particlePropertiesComponent3);


        //4 CUBES DIFFERENT TEXTURES
        TransformComponent testObjTransform;
        testObjTransform.transform  = glm::mat4(1);
        testObjTransform.transform = glm::translate(testObjTransform.transform,glm::vec3(5.0f,10.0f,0.0f));
        testObjTransform.transform =  glm::scale(testObjTransform.transform, glm::vec3(1.0f,1.0f,1.0f));
        Engine::entitySystemManager.addComponent(entities[3], testObjTransform);
        Cube testCubeMesh;
        MeshComponent testObjMeshComponent;
        testObjMeshComponent.mesh.push_back(testCubeMesh);
        Engine::entitySystemManager.addComponent(entities[3], testObjMeshComponent);


        testObjTransform.transform  = glm::mat4(1);
        testObjTransform.transform = glm::translate(testObjTransform.transform,glm::vec3(0.0f,0.0f,-10.0f));
        testObjTransform.transform =  glm::scale(testObjTransform.transform, glm::vec3(3.0f,3.0f,3.0f));
        Engine::entitySystemManager.addComponent(entities[4], testObjTransform);
        MeshComponent testObjMeshComponent1;
        testObjMeshComponent1.mesh.push_back(testCubeMesh);
        Engine::entitySystemManager.addComponent(entities[4], testObjMeshComponent1);
        testObjTransform.transform  = glm::mat4(1);
        testObjTransform.transform = glm::translate(testObjTransform.transform,glm::vec3(5.0f,0.0f,0.0f));
        testObjTransform.transform =  glm::scale(testObjTransform.transform, glm::vec3(3.0f,3.0f,3.0f));
        Engine::entitySystemManager.addComponent(entities[5], testObjTransform);
        MeshComponent testObjMeshComponent2;
        testObjMeshComponent2.mesh.push_back(testCubeMesh);
        Engine::entitySystemManager.addComponent(entities[5], testObjMeshComponent2);
        testObjTransform.transform  = glm::mat4(1);
        testObjTransform.transform = glm::translate(testObjTransform.transform,glm::vec3(-5.0f,0.0f,0.0f));
        testObjTransform.transform =  glm::scale(testObjTransform.transform, glm::vec3(3.0f,3.0f,3.0f));
        Engine::entitySystemManager.addComponent(entities[6], testObjTransform);
        MeshComponent testObjMeshComponent3;
        testObjMeshComponent3.mesh.push_back(testCubeMesh);
        Engine::entitySystemManager.addComponent(entities[6], testObjMeshComponent3);
        testObjTransform.transform  = glm::mat4(1);
        testObjTransform.transform = glm::translate(testObjTransform.transform,glm::vec3(-20.0f,0.0f,0.0f));
        testObjTransform.transform =  glm::scale(testObjTransform.transform, glm::vec3(10.0f,10.0f,3.0f));
        Engine::entitySystemManager.addComponent(entities[7], testObjTransform);
        MeshComponent testObjMeshComponent4;
        testObjMeshComponent4.mesh.push_back(testCubeMesh);
        Engine::entitySystemManager.addComponent(entities[7], testObjMeshComponent4);

        auto particleSystem =Engine::entitySystemManager.getSystem<ParticleSystem>();
        particleSystem->init();

        //FRAMEBUFFER
        FramebufferSpecification framebufferSpecification;
        framebufferSpecification.width= windowPtr->getWidth();
        framebufferSpecification.height= windowPtr->getHeight();
        frameBuffer =  std::make_shared<FrameBuffer>(framebufferSpecification);
        //FRAMEBUFFER


        //LIGHTNING
        TransformComponent ligthingCubeTransform;
        ligthingCubeTransform.transform = glm::mat4(1);
        ligthingCubeTransform.transform = glm::translate(ligthingCubeTransform.transform, glm::vec3(-5.0f, 0.0f, 0.0f));
        ligthingCubeTransform.transform = glm::scale(ligthingCubeTransform.transform, glm::vec3(1.0f, 1.0f, 1.0f));
        Engine::entitySystemManager.addComponent(entities[8], ligthingCubeTransform);
        Cube ligthingCube;
        MeshComponent lightningMeshComponent1;
        lightningMeshComponent1.mesh.push_back(ligthingCube);
        Engine::entitySystemManager.addComponent(entities[8], lightningMeshComponent1);

        ligthingCubeTransform.transform = glm::mat4(1);
        ligthingCubeTransform.transform = glm::translate(ligthingCubeTransform.transform, glm::vec3(0.0f, 0.0f, 0.0f));
        ligthingCubeTransform.transform = glm::scale(ligthingCubeTransform.transform, glm::vec3(3.0f, 3.0f, 3.0f));
        Engine::entitySystemManager.addComponent(entities[9], ligthingCubeTransform);
        MeshComponent lightningMeshComponent2;
        lightningMeshComponent2.mesh.push_back(ligthingCube);
        Engine::entitySystemManager.addComponent(entities[9], lightningMeshComponent2);
        // LIGHTNING
    }
    void LabScene::input(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(LabScene::windowClose));
        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(LabScene::onKeyPressedInput));
        dispatcher.dispatch<MouseButtonPressed>(BIND_EVENT_FUNCTION(LabScene::onMousePressed));
        dispatcher.dispatch<MouseButtonReleased>(BIND_EVENT_FUNCTION(LabScene::onMouseReleased));
        dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(LabScene::onMouseMovedEvent));
    }
    void LabScene::update(float dt) {
        currentDeltaTime =dt;
        ImGUITest();
        timeCounter = glfwGetTime();

        DrawCallSettings  testSettings;
        testSettings.enableBlendingFlag=true;
        testSettings.enableDepthTestFlag=true;
        Renderer::getInstance()->clear(glm::vec4(0.862, 0.984, 0.996, 1.0));
        Renderer::getInstance()->beginDraw(glm::mat4(1), testSettings);
        view = camera.GetViewMatrix();

        switch (item_current_idx) {
            case 0:
                texturesLab();
                break;
            case 1:
                particlesLab();
                break;
            case 2:
                shadersLab();
                break;
            case 3:
                lightsLab();
                break;
        }

        Renderer::getInstance()->endDraw();
        //POP SCENE IN PROPER WAY DONT REMOVE!
        //if(timeCounter>5){
        //    Renderer::getInstance()->clear();
        //    Engine::sceneManager.popScene();
        //    return;
        //}
    }
    bool LabScene::windowClose(WindowCloseEvent& e){
        Engine::isRunning = false;
        return true;
    }

    bool LabScene::onKeyPressedInput(KeyPressedEvent& e){

        switch (e.getKeyCode()) {
            case W:
                camera.processKeyboard(Camera_Movement::FORWARD_CAMERA_MOVE,10* currentDeltaTime);
                break;
            case A:
                camera.processKeyboard(Camera_Movement::LEFT_CAMERA_MOVE, 10* currentDeltaTime);
                break;
            case S:
                camera.processKeyboard(Camera_Movement::BACKWARD_CAMERA_MOVE, 10* currentDeltaTime);
                break;
            case D:
                camera.processKeyboard(Camera_Movement::RIGHT_CAMERA_MOVE, 10* currentDeltaTime);
                break;
        }
        return  true;
    }
    bool LabScene::onMouseMovedEvent(MouseMovedEvent& e){
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


    bool LabScene::onMousePressed(MouseButtonPressed &e) {
        if(e.getMouseCode() ==ButtonLeft){
            isButtonPressed =true;
        }
        if(e.getMouseCode() ==ButtonRight){
            camera.front= glm::vec3(0.0f, 0.0f, -1.0f);
        }
        return true;
    }
    bool LabScene::onMouseReleased(MouseButtonReleased& e){
        if(e.getMouseCode() ==ButtonLeft){
            isButtonPressed = false;
        }
        return true;
    }

    void LabScene::ImGUITest() {
        static bool testBool = true;
        //DENGINE_TRACE("SCENE IS UPDATING: {} ", getSceneName());
        float col[3]{0,0,0};


        ImGui::Begin("Properties");
        //if (ImGui::CollapsingHeader("Scene")){
        //    ImGui::ShowDemoWindow(&testBool);
        //}
        if (ImGui::CollapsingHeader("Laboratoria")) {
            const char* items[] = { "Textures Lab", "Particles Lab", "Shaders Lab", "Lights Lab", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
            if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {

                    if (ImGui::Selectable(items[n], is_selected)) {
                        item_current_idx = n;
                        is_selected = true;
                    }
                    // Set the initial focus when opening the combo (scrolling + keyboard navigation focus)
                    if (is_selected){
                        DENGINE_TRACE("SELECTED {}",item_current_idx);
                    }

                    //ImGui::SetItemDefaultFocus();
                }
                ImGui::EndListBox();
            }
            //if(is_selected ){
            //    transformEditorDraw();
            //}
        }
        ImGui::End();
    }
    void LabScene::particlesLab() {
        Renderer::getInstance()->clear(glm::vec4(0.862, 0.984, 0.996, 1.0));
        auto particleSystem = Engine::entitySystemManager.getSystem<ParticleSystem>();
        particleSystem->update(currentDeltaTime, projection, view);
    }

    void LabScene::texturesLab() {
        frameBuffer->bind();
        Renderer::getInstance()->clear(glm::vec4(0.3, 0.4, 0.996, 1.0));
        testShader.bind();
        textureTest.bind(0);
        testShader.setUniform1i("u_Texture", 0);
        for (const auto &ent: entities) {
            if (Engine::entitySystemManager.hasComponent<MeshComponent>(ent)) {
                testShader.setUniformMat4f("projection", projection);
                testShader.setUniformMat4f("view", view);
                testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(
                        ent).transform);
                Renderer::getInstance()->draw(
                        Engine::entitySystemManager.getComponent<MeshComponent>(ent).mesh.at(0), testShader);
            }
        }
        textureTest.unbind();
        frameBuffer->unBind();

        Renderer::getInstance()->clear(glm::vec4(0.862, 0.984, 0.996, 1.0));

        testShader.bind();
        frameBuffer->bindTexture(0);
        testShader.setUniform1i("u_Texture", 0);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[7])) {
            testShader.setUniformMat4f("projection", projection);
            testShader.setUniformMat4f("view", view);
            testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>( entities[7]).transform);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[7]).mesh.at(0), testShader);
        }

        multTextureShader.bind();
        firstToMultiTexturing.bind(0);
        secondToMultiTexturing.bind(1);
        thirdToMultiTexturing.bind(2);
        multTextureShader.setUniform1i("u_Texture0", 0);
        multTextureShader.setUniform1i("u_Texture1", 1);
        multTextureShader.setUniform1i("u_Texture2", 2);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[6])) {
            multTextureShader.setUniformMat4f("projection", projection);
            multTextureShader.setUniformMat4f("view", view);
            multTextureShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>( entities[6]).transform);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[6]).mesh.at(0), multTextureShader);
        }
        firstToMultiTexturing.unbind();
        secondToMultiTexturing.unbind();
        thirdToMultiTexturing.unbind();


        multiTexture2Shader.bind();
        thirdToMultiTexturing.bind(0);
        dengineTexture.bind(1);
        multiTexture2Shader.setUniform1i("u_Texture0", 0);
        multiTexture2Shader.setUniform1i("u_Texture1", 1);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[5])) {
            multiTexture2Shader.setUniformMat4f("projection", projection);
            multiTexture2Shader.setUniformMat4f("view", view);
            multiTexture2Shader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>( entities[5]).transform);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[5]).mesh.at(0), multiTexture2Shader);
        }

        testShader.bind();
        dengineTexture.bind(0);
        testShader.setUniform1i("u_Texture", 0);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[4])) {
            testShader.setUniformMat4f("projection", projection);
            testShader.setUniformMat4f("view", view);
            testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>( entities[4]).transform);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[4]).mesh.at(0), testShader);
        }
        textureTest.unbind();

        testShader.bind();
        textureTest.bind(0);
        testShader.setUniform1i("u_Texture", 0);
        for (auto i =0u; i<(entities.size()-6u);i++) {
            if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[i])) {
                testShader.setUniformMat4f("projection", projection);
                testShader.setUniformMat4f("view", view);
                testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(
                        entities[i]).transform);
                Renderer::getInstance()->draw(
                        Engine::entitySystemManager.getComponent<MeshComponent>(entities[i]).mesh.at(0), testShader);
            }
        }
        textureTest.unbind();
    }

    void LabScene::shadersLab() {

    }

    void LabScene::lightsLab() {
        Renderer::getInstance()->clear(glm::vec4(0.3, 0.4, 0.7, 1.0));
        testShader.bind();
        textureTest.bind(0);
        testShader.setUniform1i("u_Texture", 0);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[8]))
        {
                testShader.setUniformMat4f("projection", projection);
                testShader.setUniformMat4f("view", view);
                testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[8]).transform);
                Renderer::getInstance()->draw(
                    Engine::entitySystemManager.getComponent<MeshComponent>(entities[8]).mesh.at(0), testShader);
        }
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[9]))
        {
            testShader.setUniformMat4f("projection", projection);
            testShader.setUniformMat4f("view", view);
            testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[9]).transform);
            Renderer::getInstance()->draw(
                Engine::entitySystemManager.getComponent<MeshComponent>(entities[9]).mesh.at(0), testShader);
        }

        textureTest.unbind();
    }
}