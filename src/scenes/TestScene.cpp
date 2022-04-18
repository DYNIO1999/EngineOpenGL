#include "TestScene.h"
#include "core/LogManager.h"
#include "core/Engine.h"

#include "core/Random.h"
#include "components/Components.h"
#include "glm/ext.hpp"
#include "glm/gtx/string_cast.hpp"

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



        //0.0f, 0.0f,
        //1.0f, 0.0f,
        //0.5f, 1.0f
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

        testMesh = std::make_shared<Mesh>(myData, myIndexData);
        testMesh = std::make_shared<Mesh>(myData);

        entities.emplace_back(Engine::entitySystemManager.createEntity());
        //entities.emplace_back(Engine::entitySystemManager.createEntity());
        //entities.emplace_back(Engine::entitySystemManager.createEntity());
        //entities.emplace_back(Engine::entitySystemManager.createEntity());
        //entities.emplace_back(Engine::entitySystemManager.createEntity());

        TransformComponent testComp;
        MeshComponent testMeshComp{};

        testMeshComp.meshes.emplace_back(testMesh);

        testComp.transform = glm::mat4(1.0f);
        testComp.transform = glm::translate(testComp.transform, glm::vec3(0,1,-10));
        testComp.transform  = glm::rotate(testComp.transform, glm::radians(-10.0f), glm::vec3(1.0f, 0.0f,0.0f));
        Engine::entitySystemManager.addComponent(entities[0],testComp);
        Engine::entitySystemManager.addComponent(entities[0],testMeshComp);



        //testComp.transform = glm::mat4(1.0f);
        //testComp.transform = glm::translate(testComp.transform, glm::vec3(-1,-2,0));
        //Engine::entitySystemManager.addComponent(entities[1],testComp);
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

        nParticles  = glm::ivec3(100,100,100);
        time = 0.0f;
        deltaT=0.0f;
        speed = 35.0f;
        angle =0.0f;
        bh1 =glm::vec4(5,0,0,1);
        bh2 =glm::vec4(-5,0,0,1);
        totalParticles = nParticles.x * nParticles.y * nParticles.z;

        // Initial positions of the particles
        std::vector<GLfloat> initPos;

        std::vector<GLfloat> initVel(totalParticles * 4, 0.0f);
        glm::vec4 p(0.0f, 0.0f, 0.0f, 1.0f);
        GLfloat dx = 2.0f / (nParticles.x - 1),
                dy = 2.0f / (nParticles.y - 1),
                dz = 2.0f / (nParticles.z - 1);
        // We want to center the particles at (0,0,0)
        glm::mat4 transf = glm::translate(glm::mat4(1.0f), glm::vec3(-1,-1,-1));
        for( int i = 0; i < nParticles.x; i++ ) {
            for( int j = 0; j < nParticles.y; j++ ) {
                for( int k = 0; k < nParticles.z; k++ ) {
                    p.x = dx * i;
                    p.y = dy * j;
                    p.z = dz * k;
                    p.w = 1.0f;
                    p = transf * p;
                    initPos.push_back(p.x);
                    initPos.push_back(p.y);
                    initPos.push_back(p.z);
                    initPos.push_back(p.w);
                }
            }
        }

        // We need buffers for position , and velocity.
        GLuint bufs[2];
        glGenBuffers(2, bufs);
        GLuint posBuf = bufs[0];
        GLuint velBuf = bufs[1];

        GLuint bufSize = totalParticles * 4 * sizeof(GLfloat);

        // The buffers for positions
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, posBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initPos[0], GL_DYNAMIC_DRAW);

        // Velocities
        glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, velBuf);
        glBufferData(GL_SHADER_STORAGE_BUFFER, bufSize, &initVel[0], GL_DYNAMIC_COPY);

        // Set up the VAO
        glGenVertexArrays(1, &particlesVao);
        glBindVertexArray(particlesVao);

        glBindBuffer(GL_ARRAY_BUFFER, posBuf);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        // Set up a buffer and a VAO for drawing the attractors (the "black holes")
        glGenBuffers(1, &bhBuf);
        glBindBuffer(GL_ARRAY_BUFFER, bhBuf);
        GLfloat data[] = { bh1.x, bh1.y, bh1.z, bh1.w, bh2.x, bh2.y, bh2.z, bh2.w };
        glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(GLfloat), data, GL_DYNAMIC_DRAW);

        glGenVertexArrays(1, &bhVao);
        glBindVertexArray(bhVao);

        glBindBuffer(GL_ARRAY_BUFFER, bhBuf);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(0);

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
        if( time == 0.0f ) {
            deltaT = 0.0f;
        } else {
            deltaT = dt - time;
        }
        time = dt;
        if( true ) {
            angle += speed * deltaT;
            if( angle > 360.0f ) angle -= 360.0f;
        }

        ////MESH
        //float vertices[] = {
        //        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        //        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
        //        0.0f,  0.5f, 0.0f,  0.5f, 1.0f
        //};
        //unsigned int indices[] ={
        //        0, 1, 2,   // first triangle
        //        1, 2, 0
        //};
        ////MESH
        //VertexBuffer testVertexData(vertices, sizeof(vertices), sizeof(vertices)/sizeof(float));
        ////IndexBuffer testIndexBuffer(indices, sizeof(indices));
        //VertexBufferLayout testLayout;
        //testLayout.push<float>(3);
        //testLayout.push<float>(2);
        //VertexArray testVertexArray;
        //testVertexArray.addBuffer(testVertexData, testLayout);

        DrawCallSettings  testSettings;
        testSettings.enableBlendingFlag=true;
        Renderer::getInstance()->clear(glm::vec4(0.5, 0.5, 0.5 , 1.0));
        Renderer::getInstance()->beginDraw(glm::mat4(1), testSettings);
        view = camera.GetViewMatrix();

        textureTest.bind();
        testShader.bind();
        testShader.setUniform1i("u_Texture",0);
        testShader.setUniformMat4f("projection",projection);
        testShader.setUniformMat4f("view",view);
        for (const auto& ent: entities) {
            testShader.setUniformMat4f("model", model);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(ent), testShader);
        }
        textureTest.unbind();
        testShader.unbind();



        //Particles Compute Shader...
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0,0,1));
        glm::vec3 att1 = glm::vec3(rot*bh1);
        glm::vec3 att2 = glm::vec3(rot*bh2);

        // Execute the compute shader
        particleComputeShader.bind();
        particleComputeShader.setUniformVec3f("BlackHolePos1", att1);
        particleComputeShader.setUniformVec3f("BlackHolePos2", att2);
        glDispatchCompute(totalParticles / 1000, 1, 1);
        glMemoryBarrier( GL_SHADER_STORAGE_BARRIER_BIT );


        particleShader.bind();
        particleShader.setUniformMat4f("model",model);
        particleShader.setUniformMat4f("view", view);
        particleShader.setUniformMat4f("projection", projection);


        glPointSize(1.0f);
        particleShader.setUniformVec4f("u_Color", glm::vec4(1,0.5,0,0.2f));
        glBindVertexArray(particlesVao);
        glDrawArrays(GL_POINTS,0, totalParticles);
        glBindVertexArray(0);

        // Draw the attractors
        glPointSize(5.0f);
        GLfloat data[] = { att1.x, att1.y, att1.z, 1.0f, att2.x, att2.y, att2.z, 1.0f };
        glBindBuffer(GL_ARRAY_BUFFER, bhBuf);
        glBufferSubData( GL_ARRAY_BUFFER, 0, 8 * sizeof(GLfloat), data );
        particleShader.setUniformVec4f("u_Color", glm::vec4(1,1,0,1.0f));
        glBindVertexArray(bhVao);
        glDrawArrays(GL_POINTS, 0, 2);
        glBindVertexArray(0);

        Renderer::getInstance()->endDraw();


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