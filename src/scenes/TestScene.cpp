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
        if(!closed){
            for(auto it = entities.begin();it<entities.end();it++){
                std::cout<<*it<<' ';
                Engine::entitySystemManager.destroyEntity(*it);
            }
            std::cout<<'\n';
        }

    }
    void TestScene::initData() {
        projection  = glm::perspective(glm::radians(45.0f), (float)1600/900, 0.1f, 100.0f);


        glm::vec3 cameraPos(0.0f,0.0f,20.0f);
        view = glm::lookAt(cameraPos,
                           cameraPos+glm::vec3(0.0f, 0.0f, -1.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::mat4(1.0f);

        entities.emplace_back(Engine::entitySystemManager.createEntity());
        entities.emplace_back(Engine::entitySystemManager.createEntity());
        entities.emplace_back(Engine::entitySystemManager.createEntity());
        entities.emplace_back(Engine::entitySystemManager.createEntity());

        TransformComponent testComp;
        testComp.transform = glm::mat4(1.0f);
        testComp.transform = glm::translate(testComp.transform, glm::vec3(1,2,0));
        Engine::entitySystemManager.addComponent(entities[0],testComp);
        testComp.transform = glm::mat4(1.0f);
        testComp.transform = glm::translate(testComp.transform, glm::vec3(-1,-2,0));
        Engine::entitySystemManager.addComponent(entities[1],testComp);
        testComp.transform = glm::mat4(1.0f);
        testComp.transform = glm::translate(testComp.transform, glm::vec3(0,-2,0));
        Engine::entitySystemManager.addComponent(entities[2],testComp);
        testComp.transform = glm::mat4(1.0f);
        testComp.transform = glm::translate(testComp.transform, glm::vec3(0,0,-2));
        Engine::entitySystemManager.addComponent(entities[3],testComp);

    }
    void TestScene::input(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(TestScene::windowClose));
    }
    void TestScene::update(float dt) {
        ImGUITest();
        timeCounter = glfwGetTime();
        DENGINE_TRACE("TIME:{}",timeCounter);


        //MESH
        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
                0.0f,  0.5f, 0.0f,  0.5f, 1.0f
        };
        unsigned int indices[] ={
                0, 1, 2,   // first triangle
                1, 2, 0
        };
        //MESH

        VertexBuffer testVertexData(vertices, sizeof(vertices), sizeof(vertices)/sizeof(float));
        //IndexBuffer testIndexBuffer(indices, sizeof(indices));
        VertexBufferLayout testLayout;
        testLayout.push<float>(3);
        testLayout.push<float>(2);
        VertexArray testVertexArray;
        testVertexArray.addBuffer(testVertexData, testLayout);

        DrawCallSettings  testSettings;
        Renderer::getInstance()->clear(glm::vec4(0.5, 0.5, 0.5 , 1.0));
        Renderer::getInstance()->beginDraw(glm::mat4(1), testSettings);
        textureTest.bind();
        testShader.bind();
        testShader.setUniform1i("u_Texture",0);
        testShader.setUniformMat4f("projection",projection);
        testShader.setUniformMat4f("view",view);
        for (const auto& ent: entities) {
            testShader.setUniformMat4f("model",Engine::entitySystemManager.getComponent<TransformComponent>(ent).transform);
            Renderer::getInstance()->draw(testVertexArray, testShader);
        }
        Renderer::getInstance()->endDraw();

        textureTest.unbind();
        testShader.unbind();

        if(timeCounter>5){
            Renderer::getInstance()->clear();
            Engine::sceneManager.popScene();
            return;
        }
    }
    bool TestScene::windowClose(WindowCloseEvent& e){
        DENGINE_ERROR("IAM HEREEEE");
        closed = true;
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