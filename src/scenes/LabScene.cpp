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

    void LabScene::editorLightsLab(){
        ImGui::Begin("Editor");
        //if (ImGui::CollapsingHeader("Position"))
        //{
        //    ImGui::InputFloat3("Position", col);
        //}
        //if (ImGui::CollapsingHeader("Rotation"))
        //{
        //    ImGui::InputFloat3("Rotation", col);
        //}
        if (ImGui::CollapsingHeader("Ambient Light Color"))
        {
            ImGui::ColorPicker3("Color",&ambientLightColor[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);

        }
        if (ImGui::CollapsingHeader("Object Color"))
        {
            ImGui::ColorPicker3("Color", &objectColor[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
        }
        if (ImGui::CollapsingHeader("Ambient Intensity")){
            ImGui::SliderFloat(" Intensity",&ambientLightIntensity,0.0f,1.0f);
        }
        if (ImGui::CollapsingHeader("Specular Intensity")){
           ImGui::SliderFloat("Intensity", &specularLightIntensity, 0.0f, 1.0f);
        }
        ImGui::End();
    }

    void LabScene::editorShaderLab(){
        ImGui::Begin("Editor");
        if (ImGui::CollapsingHeader("Ambient Light Color"))
        {
            ImGui::ColorPicker3("Color",&ambientLightColor[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
        }
        if (ImGui::CollapsingHeader("Object Color"))
        {
            ImGui::ColorPicker3("Color", &objectColor[0], ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
        }
        if (ImGui::CollapsingHeader("Ambient Intensity")){
            ImGui::SliderFloat(" Intensity",&ambientLightIntensity,0.0f,1.0f);
        }
        if (ImGui::CollapsingHeader("Toon Levels")){
            ImGui::SliderInt("Levels", &levels, 0, 100);
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



        cubeModel = std::make_shared<Model>(PATH_MODELS+"cube.obj");
        sphereModel = std::make_shared<Model>(PATH_MODELS+"sphere.obj");
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
        entities.emplace_back(Engine::entitySystemManager.createEntity()); // 10
        entities.emplace_back(Engine::entitySystemManager.createEntity()); // 11
        entities.emplace_back(Engine::entitySystemManager.createEntity()); // 12
        //LIGHTNING CUBES

        //LIGHT SOURCE
        entities.emplace_back(Engine::entitySystemManager.createEntity()); // 13
        // LIGHT SOURCE

        //TOON SHADING
        entities.emplace_back(Engine::entitySystemManager.createEntity()); // 14

        //MODELS
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //15
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //16

        TransformComponent testComp;
        testComp.transform = glm::mat4(1.0f);

        /////SMOKE PARTICLES BEGIN
        std::shared_ptr<Shader> smokeParticleShader;
        std::shared_ptr<Shader> smokeComputeShader;

        std::shared_ptr<Shader> fogComputeShader;
        std::shared_ptr<Shader> fogParticleShader;


        fogComputeShader  = std::make_shared<Shader>(PATH_SHADERS + "particles/fog/FogComputeShader.glsl");
        fogParticleShader = std::make_shared<Shader>(PATH_SHADERS + "particles/fog/FogVertexShader.glsl",
                                                       PATH_SHADERS +"particles/fog/FogGeometryShader.glsl",
                                                       PATH_SHADERS + "particles/fog/FogFragmentShader.glsl");
        //DENGINE_ERROR("FOG PARTICLE SHADER->{}", fogParticleShader->getHandle());

        smokeComputeShader = std::make_shared<Shader>(PATH_SHADERS + "particles/smoke/SmokeComputeShader.glsl");
        smokeParticleShader = std::make_shared<Shader>(PATH_SHADERS + "particles/smoke/SmokeVertexShader.glsl",
                                                     PATH_SHADERS +"particles/smoke/SmokeGeometryShader.glsl",
                                                     PATH_SHADERS + "particles/smoke/SmokeFragmentShader.glsl");


        //DENGINE_ERROR("SMOKE PARTICLE SHADER->{}", smokeParticleShader->getHandle());
        //DENGINE_ERROR("STANDARD  SHADER->{}",testShader.getHandle());
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
        ligthingCubeTransform.transform = glm::translate(ligthingCubeTransform.transform, glm::vec3(-20.0f, 0.0f, 0.0f));
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

        ligthingCubeTransform.transform = glm::mat4(1);
        ligthingCubeTransform.transform = glm::translate(ligthingCubeTransform.transform, glm::vec3(-10.0f, 0.0f, -5.0f));
        ligthingCubeTransform.transform = glm::scale(ligthingCubeTransform.transform, glm::vec3(5.0f, 5.0f, 5.0f));
        Engine::entitySystemManager.addComponent(entities[10], ligthingCubeTransform);
        MeshComponent lightningMeshComponent3;
        lightningMeshComponent3.mesh.push_back(ligthingCube);
        Engine::entitySystemManager.addComponent(entities[10], lightningMeshComponent3);

        ligthingCubeTransform.transform = glm::mat4(1);
        ligthingCubeTransform.transform = glm::translate(ligthingCubeTransform.transform, glm::vec3(5.0f, 10.0f, 0.0f));
        ligthingCubeTransform.transform = glm::scale(ligthingCubeTransform.transform, glm::vec3(1.0f, 1.0f, 1.0f));
        Engine::entitySystemManager.addComponent(entities[11], ligthingCubeTransform);
        MeshComponent lightningMeshComponent4;
        lightningMeshComponent4.mesh.push_back(ligthingCube);
        Engine::entitySystemManager.addComponent(entities[11], lightningMeshComponent4);

        ligthingCubeTransform.transform = glm::mat4(1);
        ligthingCubeTransform.transform = glm::translate(ligthingCubeTransform.transform, glm::vec3(0.0f, 0.0f, -12.0f));
        ligthingCubeTransform.transform = glm::scale(ligthingCubeTransform.transform, glm::vec3(1.0f, 1.0f, 1.0f));
        Engine::entitySystemManager.addComponent(entities[12], ligthingCubeTransform);
        MeshComponent lightningMeshComponent5;
        lightningMeshComponent5.mesh.push_back(ligthingCube);
        Engine::entitySystemManager.addComponent(entities[12], lightningMeshComponent5);




        //LIGHT SOURCE
        ligthingCubeTransform.transform = glm::mat4(1);
        lightSourcePosition =  glm::vec3(0.0f, 20.0f, 0.0f);
        ligthingCubeTransform.transform = glm::translate(ligthingCubeTransform.transform, lightSourcePosition);
        ligthingCubeTransform.transform = glm::scale(ligthingCubeTransform.transform, glm::vec3(1.0f, 1.0f, 1.0f));
        Engine::entitySystemManager.addComponent(entities[13], ligthingCubeTransform);
        MeshComponent lightningMeshComponent6;
        lightningMeshComponent6.mesh.push_back(ligthingCube);
        Engine::entitySystemManager.addComponent(entities[13], lightningMeshComponent6);
        //LIGHT SOURCE

        ligthingCubeTransform.transform = glm::mat4(1);
        ligthingCubeTransform.transform = glm::rotate(glm::radians(30.0f),glm::vec3(0,0,-1));
        ligthingCubeTransform.transform = glm::translate(ligthingCubeTransform.transform, glm::vec3(0.0f, 20.0f, 3.0f));
        ligthingCubeTransform.transform = glm::scale(ligthingCubeTransform.transform, glm::vec3(1.0f, 1.0f, 1.0f));
        Engine::entitySystemManager.addComponent(entities[14], ligthingCubeTransform);
        MeshComponent lightningMeshComponent7;
        lightningMeshComponent6.mesh.push_back(ligthingCube);
        Engine::entitySystemManager.addComponent(entities[14], lightningMeshComponent6);
        //LIGHTNING

        //MODELS


        TransformComponent modelTransform;
        modelTransform.transform = glm::mat4(1);
        Engine::entitySystemManager.addComponent(entities[15],modelTransform);
        MeshComponent modelMeshComp;
        modelMeshComp.meshes = cubeModel->meshes;
        Engine::entitySystemManager.addComponent(entities[15], modelMeshComp);




        modelTransform.transform = glm::mat4(1);
        modelTransform.transform = glm::translate(modelTransform.transform , glm::vec3(40.0f, 0.0f,0.0f));

        MeshComponent modelMeshComp2;
        modelMeshComp2.meshes = sphereModel->meshes;
        Engine::entitySystemManager.addComponent(entities[16],modelTransform);
        Engine::entitySystemManager.addComponent(entities[16], modelMeshComp2);


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
            case 4 :
                enviromentMappingLab();
                break;
            case 5 :
                modelLoadingLab();
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
                camera.processKeyboard(Camera_Movement::FORWARD_CAMERA_MOVE,cameraSpeed* currentDeltaTime);
                break;
            case A:
                camera.processKeyboard(Camera_Movement::LEFT_CAMERA_MOVE, cameraSpeed* currentDeltaTime);
                break;
            case S:
                camera.processKeyboard(Camera_Movement::BACKWARD_CAMERA_MOVE, cameraSpeed* currentDeltaTime);
                break;
            case D:
                camera.processKeyboard(Camera_Movement::RIGHT_CAMERA_MOVE, cameraSpeed* currentDeltaTime);
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
        if(e.getMouseCode() ==ButtonRight){
            if(isButtonPressed){
                isButtonPressed =false;
            }else{
                isButtonPressed =true;
            }
        }
        return true;
    }
    bool LabScene::onMouseReleased(MouseButtonReleased& e){
        //if(e.getMouseCode() ==ButtonLeft){
        //    isButtonPressed = false;
        //}
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
            const char* items[] = { "Textures Lab", "Particles Lab", "Shaders Lab", "Lights Lab", "Environment Mapping", "Model Loading", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
            if (ImGui::BeginListBox("##listbox 2", ImVec2(-FLT_MIN, 10 * ImGui::GetTextLineHeightWithSpacing())))
            {
                for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                {

                    if (ImGui::Selectable(items[n], is_selected)) {
                        item_current_idx = n;
                        if((item_current_idx ==3) || (item_current_idx ==2)){
                            is_selected = true;
                        }else{
                            is_selected = false;
                        }
                    }
                    //ImGui::SetItemDefaultFocus();
                }
                ImGui::EndListBox();
            }
            if(is_selected) {
                switch (item_current_idx) {
                    case 0:
                        break;
                    case 1:
                        break;
                    case 2:
                        editorShaderLab();
                        break;
                    case 3:
                        editorLightsLab();
                        break;
                }
            }
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
                    if (!Engine::entitySystemManager.getComponent<MeshComponent>(ent).mesh.empty()) {
                    testShader.setUniformMat4f("projection", projection);
                    testShader.setUniformMat4f("view", view);
                    testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(
                            ent).transform);
                    Renderer::getInstance()->draw(
                            Engine::entitySystemManager.getComponent<MeshComponent>(ent).mesh.at(0), testShader);
                }
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
        for (auto i =0u; i<(entities.size()-12u);i++) {
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
        Renderer::getInstance()->clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0));
        toonShader.bind();
        toonShader.setUniformVec3f("u_Color", objectColor);
        toonShader.setUniformVec3f("u_LightPosition", lightSourcePosition);
        toonShader.setUniformVec3f("u_LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        toonShader.setUniform1f("u_AmbientIntensity", ambientLightIntensity);
        toonShader.setUniform1i("u_Levels", levels);

        //toonShader.setUniform1i("u_Levels", 4);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[14]))
        {
            toonShader.setUniformMat4f("projection", projection);
            toonShader.setUniformMat4f("view", view);
            toonShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[14]).transform);
            Renderer::getInstance()->draw(
                    Engine::entitySystemManager.getComponent<MeshComponent>(entities[14]).mesh.at(0), toonShader);
        }

        lightSourceShader.bind();
        lightSourceShader.setUniformVec4f("u_Color", glm::vec4(ambientLightColor, 1.0f));
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[13]))
        {
            lightSourceShader.setUniformMat4f("projection", projection);
            lightSourceShader.setUniformMat4f("view", view);
            lightSourceShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[13]).transform);
            Renderer::getInstance()->draw(
                    Engine::entitySystemManager.getComponent<MeshComponent>(entities[13]).mesh.at(0), lightSourceShader);
        }
    }

    void LabScene::lightsLab() {

        Renderer::getInstance()->clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0));




        glDisable(GL_BLEND);
        ambientLightShader.bind();
        ambientLightShader.setUniformVec4f("u_Color", glm::vec4(0.8, 0.352, 0.682, 1.0));
        ambientLightShader.setUniformVec4f("u_AmbientLightColor", glm::vec4(ambientLightColor, 1.0f));
        ambientLightShader.setUniform1f("u_AmbientIntensity", ambientLightIntensity);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[8]))
        {
                ambientLightShader.setUniformMat4f("projection", projection);
                ambientLightShader.setUniformMat4f("view", view);
                ambientLightShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[8]).transform);
                Renderer::getInstance()->draw(
                    Engine::entitySystemManager.getComponent<MeshComponent>(entities[8]).mesh.at(0), ambientLightShader);
        }
        diffuseLightShader.bind();
        diffuseLightShader.setUniformVec4f("u_Color", glm::vec4(objectColor, 1.0));
        diffuseLightShader.setUniformVec3f("u_LightPosition", lightSourcePosition);

        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[9]))
        {
            diffuseLightShader.setUniformMat4f("projection", projection);
            diffuseLightShader.setUniformMat4f("view", view);
            diffuseLightShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[9]).transform);
            Renderer::getInstance()->draw(
                Engine::entitySystemManager.getComponent<MeshComponent>(entities[9]).mesh.at(0), diffuseLightShader);
        }
        specularLightShader.bind();
        specularLightShader.setUniform1f("u_SpecularLight", specularLightIntensity);
        specularLightShader.setUniformVec4f("u_Color", glm::vec4(objectColor, 1.0));
        specularLightShader.setUniformVec3f("u_LightPosition", lightSourcePosition);
        specularLightShader.setUniformVec3f("u_CameraPosition", camera.position);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[10]))
        {
            specularLightShader.setUniformMat4f("projection", projection);
            specularLightShader.setUniformMat4f("view", view);
            specularLightShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[10]).transform);
            Renderer::getInstance()->draw(
                Engine::entitySystemManager.getComponent<MeshComponent>(entities[10]).mesh.at(0), specularLightShader);
        }
        phongLightShader.bind();

        phongLightShader.setUniform1f("u_AmbientIntensity", ambientLightIntensity);
        phongLightShader.setUniform1f("u_SpecularLightStrength", specularLightIntensity);
        phongLightShader.setUniformVec3f("u_Color", glm::vec3(1.0f, 0.5f, 0.31f));
        phongLightShader.setUniformVec3f("u_LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        phongLightShader.setUniformVec3f("u_LightPosition", lightSourcePosition);
        phongLightShader.setUniformVec3f("u_CameraPosition", camera.position);

        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[11]))
        {
            phongLightShader.setUniformMat4f("projection", projection);
            phongLightShader.setUniformMat4f("view", view);
            phongLightShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[11]).transform);
            Renderer::getInstance()->draw(
                Engine::entitySystemManager.getComponent<MeshComponent>(entities[11]).mesh.at(0), phongLightShader);
        }

        blinnphongLightShader.bind();

        blinnphongLightShader.setUniform1f("u_AmbientIntensity", ambientLightIntensity);
        blinnphongLightShader.setUniform1f("u_SpecularLightStrength", specularLightIntensity);
        blinnphongLightShader.setUniformVec3f("u_Color", glm::vec3(1.0f, 0.5f, 0.31f));
        blinnphongLightShader.setUniformVec3f("u_LightColor", glm::vec3(1.0f, 1.0f, 1.0f));
        blinnphongLightShader.setUniformVec3f("u_LightPosition", lightSourcePosition);
        blinnphongLightShader.setUniformVec3f("u_CameraPosition", camera.position);
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[12]))
        {
            blinnphongLightShader.setUniformMat4f("projection", projection);
            blinnphongLightShader.setUniformMat4f("view", view);
            blinnphongLightShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[12]).transform);
            Renderer::getInstance()->draw(
                Engine::entitySystemManager.getComponent<MeshComponent>(entities[12]).mesh.at(0), blinnphongLightShader);
        }

        lightSourceShader.bind();
        lightSourceShader.setUniformVec4f("u_Color", glm::vec4(ambientLightColor, 1.0f));
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[13]))
        {
            lightSourceShader.setUniformMat4f("projection", projection);
            lightSourceShader.setUniformMat4f("view", view);
            lightSourceShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[13]).transform);
            Renderer::getInstance()->draw(
                Engine::entitySystemManager.getComponent<MeshComponent>(entities[13]).mesh.at(0), lightSourceShader);
        }
        glEnable(GL_BLEND);
    }


    void LabScene::enviromentMappingLab() {
        Renderer::getInstance()->clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0));
    }

    void LabScene::modelLoadingLab() {
        Renderer::getInstance()->clear(glm::vec4(0.862, 0.984, 0.996, 1.0));

        /*
        if (Engine::entitySystemManager.hasComponent<MeshComponent>(entities[i])) {
            testShader.setUniformMat4f("projection", projection);
            testShader.setUniformMat4f("view", view);
            testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(
                    entities[i]).transform);
            Renderer::getInstance()->draw(
                    Engine::entitySystemManager.getComponent<MeshComponent>(entities[i]).mesh.at(0), testShader);
        }*/


       // for (const auto& it : Engine::entitySystemManager.getComponent<MeshComponent>(entities[15]).meshes) {
       //     DENGINE_ERROR("VERTICES -->{}" , it->vertices.size());
       //     DENGINE_ERROR("VERTICES -->{}" , testModel->meshes[0]->vertices.size());
       // }


        testShader.bind();
        testShader.setUniformMat4f("projection", projection);
        testShader.setUniformMat4f("view", view);
        testShader.setUniformMat4f("model", glm::mat4(1));
        //DENGINE_INFO("MESHES{}",testModel->meshes.size());
        //DENGINE_INFO("INDICES {}",testModel->meshes[0].indices.size());
        //DENGINE_INFO("VERTICES{}",testModel->meshes[0].vertices.size());
        //testModel->meshes[0].getVertexArrayObj()->bind();
        //testModel->meshes[0].getIndexBufferObj()->bind();

        // testShader.bind();
       // testShader.setUniformMat4f("projection", projection);
       // testShader.setUniformMat4f("view", view);
       // testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[15]).transform);
       //    // DENGINE_INFO("SIZE: {}", Engine::entitySystemManager.getComponent<MeshComponent>(entities[15]).meshes.size());
       Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[15]), testShader);


        testShader.bind();
        testShader.setUniformMat4f("projection", projection);
        testShader.setUniformMat4f("view", view);
        testShader.setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[16]).transform);

        Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[16]), testShader);



    }
}