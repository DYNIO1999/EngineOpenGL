#include "TestScene.h"
#include "core/LogManager.h"
#include "core/Engine.h"

#include "core/Random.h"
#include "components/Components.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

#include "particles/PointEmitter.h"

namespace DEngine{



    static glm::mat3 makeArbitraryBasis( const glm::vec3 & dir ) {
        glm::mat3 basis;
        glm::vec3 u, v, n;
        v = dir;
        n = glm::cross(glm::vec3(1,0,0), v);
        if( glm::length(n) < 0.00001f ) {
            n = glm::cross(glm::vec3(0,1,0), v);
        }
        u = glm::cross(v,n);
        basis[0] = glm::normalize(u);
        basis[1] = glm::normalize(v);
        basis[2] = glm::normalize(n);
        return basis;
    }


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
    TestScene::~TestScene(){
    }
    void TestScene::detach() {
            for(auto it = entities.begin();it<entities.end();it++){

                std::cout<<*it<<' ';

                Engine::entitySystemManager.destroyEntity(*it);

            }
            std::cout<<'\n';
    }

    void TestScene::initData() {
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
        entities.emplace_back(Engine::entitySystemManager.createEntity());
        entities.emplace_back(Engine::entitySystemManager.createEntity());
        entities.emplace_back(Engine::entitySystemManager.createEntity());
        //entities.emplace_back(Engine::entitySystemManager.createEntity());
        //entities.emplace_back(Engine::entitySystemManager.createEntity());

        TransformComponent testComp;
        //MeshComponent testMeshComp{};
        //testMeshComp.mesh= testModel->meshes;

        testComp.transform = glm::mat4(1.0f);
        testComp.transform = glm::translate(testComp.transform, glm::vec3(0,1,-10));
        testComp.transform  = glm::rotate(testComp.transform, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f,0.0f));
        Engine::entitySystemManager.addComponent(entities[0],testComp);
        //Engine::entitySystemManager.addComponent(entities[0],testMeshComp);



        testComp.transform = glm::mat4(1.0f);

        ParticleProps testProps;
        testProps.color = glm::vec4(1,1,0.5,1);
        testProps.size = 5.0f;

        //ParticleComponent particleComponent;
        //particleComponent.particleProps = testProps;
        //particleComponent.texture = nullptr;
        //particleComponent.emitter = std::make_shared<PointEmitter>(glm::ivec3(100,100,100));
        //particleComponent.particleShader = std::make_shared<Shader>(PATH_SHADERS+ "particles/ParticleVertexShader.glsl",PATH_SHADERS+ "particles/ParticleFragmentShader.glsl");
        //particleComponent.computeShader = std::make_shared<Shader>(PATH_SHADERS +"particles/ParticleComputeShader.glsl");


        Engine::entitySystemManager.addComponent(entities[1],testComp);
        //Engine::entitySystemManager.addComponent(entities[1], particleComponent);



        testComp.transform = glm::mat4(1.0f);
        ParticleProps testProps2;
        testProps2.color = glm::vec4(1,0.3,0.7,1);
        testProps2.size = 5.0f;
        testProps2.workGroups =2;

        Engine::entitySystemManager.addComponent(entities[2],testComp);
        //testComp.transform = glm::mat4(1.0f);
        //testComp.transform = glm::translate(testComp.transform, glm::vec3(0,-2,0));
        //Engine::entitySystemManager.addComponent(entities[2],testComp);
        //testComp.transform = glm::mat4(1.0f);
        //testComp.transform = glm::translate(testComp.transform, glm::vec3(0,0,-2));
        //Engine::entitySystemManager.addComponent(entities[3],testComp);
        //ParticleCPUEmitterComponent testEmitter;
        //testComp.transform = glm::mat4(1.0f);
        //testComp.transform = glm::translate(testComp.transform, glm::vec3(0,0,-2));
        //Engine::entitySystemManager.addComponent(entities[4],testComp);
        //Engine::entitySystemManager.addComponent(entities[4],testEmitter);

       // auto particleSystem =Engine::entitySystemManager.getSystem<ParticleSystem>();
       // particleSystem->init();
        computeShader      = std::make_shared<Shader>(PATH_SHADERS + "particles/smoke/SmokeComputeShader.glsl");
        smokeParticleShader = std::make_shared<Shader>(PATH_SHADERS + "particles/smoke/SmokeVertexShader.glsl",
                                                                              PATH_SHADERS + "particles/smoke/SmokeFragmentShader.glsl");

        std::vector<float> initialPositions;
        std::vector<float> initialVelocities;
        std::vector<float> initialAge;
        totalParticles =1000;
        glGenBuffers(1, &posBuf);
        glGenBuffers(1, &velBuf);
        glGenBuffers(1, &age);


        glm::vec4 p(0.0f, 0.0f, 0.0f, 1.0f);
        glm::mat4 transf = glm::translate(glm::mat4(1.0f), glm::vec3(-1,-1,-1));
        for( int i = 0; i < totalParticles; ++i ) {
            p.x = 0.0f;
            p.y = 0.0f;
            p.z = 0.0f;
            p.w = 1.0f;
            p = transf * p;
            initialPositions.push_back(p.x);
            initialPositions.push_back(p.y);
            initialPositions.push_back(p.z);
            initialPositions.push_back(p.w);
        }
        float theta, phi;
        for( int i = 0; i < totalParticles; ++i) {
            theta = glm::mix(0.0f, glm::pi<float>() / 6.0f, Random::randomFloat(0.0f, 10.0f));
            phi = glm::mix(0.0f, glm::two_pi<float>(), Random::randomFloat(0.0f, 10.0f));

            p.x =sinf(theta) * cosf(phi);
            p.y =cosf(theta);
            p.z = sinf(theta) * sinf(phi);
            p.w = 0;
            initialVelocities.push_back(p.x);
            initialVelocities.push_back(p.y);
            initialVelocities.push_back(p.z);
            initialVelocities.push_back(p.w);
        }


        for( int i = 0; i < totalParticles; ++i) {
            initialAge.push_back(0.0f);
        }

        uint bufSize = totalParticles * 4 * sizeof(float);
        uint bufSizeAge = totalParticles * sizeof(float);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, posBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initialPositions[0], GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initialVelocities[0], GL_DYNAMIC_DRAW);
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 2, age);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSizeAge, &initialAge[0], GL_DYNAMIC_DRAW);

        glGenVertexArrays(1, &particlesVao);
        glBindVertexArray(particlesVao);
        glBindBuffer(GL_ARRAY_BUFFER, posBuf);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glBindVertexArray(0);


    }
    void TestScene::input(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(TestScene::windowClose));
        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(TestScene::onKeyPressedInput));
        dispatcher.dispatch<MouseButtonPressed>(BIND_EVENT_FUNCTION(TestScene::onMousePressed));
        dispatcher.dispatch<MouseButtonReleased>(BIND_EVENT_FUNCTION(TestScene::onMouseReleased));
        dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(TestScene::onMouseMovedEvent));
    }
    void TestScene::update(float dt) {
        currentDeltaTime =dt;
        ImGUITest();
        timeCounter = glfwGetTime();
        DENGINE_TRACE("TIME:{}",timeCounter);

        DrawCallSettings  testSettings;
        testSettings.enableBlendingFlag=true;
        testSettings.enableDepthTestFlag=true;
        Renderer::getInstance()->clear(glm::vec4(0.5, 0.5, 0.5 , 1.0));
        Renderer::getInstance()->beginDraw(glm::mat4(1), testSettings);
        view = camera.GetViewMatrix();
        //textureTest.bind();
        //testShader.bind();
        ////testShader.setUniform1i("u_Texture",0);
        //testShader.setUniformMat4f("projection",projection);
        //testShader.setUniformMat4f("view",view);
        //testShader.setUniformMat4f("model",model);
        //for (const auto& ent: entities) {
        //    if(Engine::entitySystemManager.hasComponent<MeshComponent>(ent)) {
        //        for(size_t it =0 ; it<Engine::entitySystemManager.getComponent<MeshComponent>(ent).mesh.size();it++) {
        //            //testShader.setUniformMat4f("model", model);
        //            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(ent).mesh.at(it), testShader);
        //        }
        //    }
        //}
        //textureTest.unbind();


        //smokeShader.bind();
        //smokeShader.setUniformMat4f("projection",projection);
        //smokeShader.setUniformMat4f("view",view);
        //smokeShader.setUniformMat4f("model",model);
        //smokeShader.setUniform1f("u_Time", dt);


        computeShader->bind();
        //computeShader->setUniformMat3f("EmitterBasis",makeArbitraryBasis(emitterDir));
        //computeShader->setUniformMat4f("EmitterBasis",glm::mat4(makeArbitraryBasis(emitterDir)));
        computeShader->setUniform1f("DeltaTime",dt);
        glDispatchCompute(1000, 1, 1);
        glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);


        smokeParticleShader->bind();
        smokeParticleShader->setUniformVec4f("u_Color",glm::vec4(1.0f,0.5f,0.3f,1.0f));
        smokeParticleShader->setUniformMat4f("u_MVP",projection*view*model);
        glBindVertexArray(particlesVao);
        glPointSize(15.0f);
        glDrawArrays(GL_POINTS,0, totalParticles);
        //Renderer::getInstance()->draw(*vaObj,smokeShader,GL_POINTS);
        //smokeShader.unbind();

        Renderer::getInstance()->endDraw();
     //   auto particleSystem =Engine::entitySystemManager.getSystem<ParticleSystem>();
        //particleSystem->update(dt, projection*view*model);

        //POP SCENE IN PROPER WAY DONT REMOVE!
        //if(timeCounter>5){
        //    Renderer::getInstance()->clear();
        //    Engine::sceneManager.popScene();
        //    return;
        //}
    }
    bool TestScene::windowClose(WindowCloseEvent& e){
        Engine::isRunning = false;
        return true;
    }

    bool TestScene::onKeyPressedInput(KeyPressedEvent& e){

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
    bool TestScene::onMouseMovedEvent(MouseMovedEvent& e){
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


    bool TestScene::onMousePressed(MouseButtonPressed &e) {
        if(e.getMouseCode() ==ButtonLeft){
            isButtonPressed =true;
        }
        if(e.getMouseCode() ==ButtonRight){
            camera.front= glm::vec3(0.0f, 0.0f, -1.0f);
        }
        return true;
    }
    bool TestScene::onMouseReleased(MouseButtonReleased& e){
        if(e.getMouseCode() ==ButtonLeft){
            isButtonPressed = false;
        }
        return true;
    }

    void TestScene::ImGUITest() {
        static bool testBool = true;
        //DENGINE_TRACE("SCENE IS UPDATING: {} ", getSceneName());
        float col[3]{0,0,0};


        ImGui::Begin("Properties");
        if (ImGui::CollapsingHeader("Scene")){
            ImGui::ShowDemoWindow(&testBool);
        }
        if (ImGui::CollapsingHeader("Entities")) {
            const char* items[] = { "AAAA", "BBBB", "CCCC", "DDDD", "EEEE", "FFFF", "GGGG", "HHHH", "IIII", "JJJJ", "KKKK", "LLLLLLL", "MMMM", "OOOOOOO" };
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
            if(is_selected ){
                transformEditorDraw();
            }
        }
        ImGui::End();
    }
}