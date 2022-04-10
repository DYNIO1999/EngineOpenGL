#include "TestScene.h"
#include "core/LogManager.h"
#include "core/Engine.h"

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
    void TestScene::input(Event &e) {
        //std::cout<<e.getName()<<'\n';
    }
    void TestScene::update() {
        ImGUITest();
        float vertices[] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
                0.0f,  0.5f, 0.0f,  0.5f, 1.0f
        };
        unsigned int indices[] ={
                0, 1, 2,   // first triangle
                1, 2, 0
        };

        VertexBuffer testVertexData(vertices, sizeof(vertices), sizeof(vertices)/sizeof(float));
        //IndexBuffer testIndexBuffer(indices, sizeof(indices));
        VertexBufferLayout testLayout;
        testLayout.push<float>(3);
        testLayout.push<float>(2);
        VertexArray testVertexArray;
        testVertexArray.addBuffer(testVertexData, testLayout);

        textureTest.bind();
        testShader.bind();
        testShader.setUniform1i("u_Texture",0);

        DrawCallSettings  testSettings;
        Renderer::getInstance()->clear(glm::vec4(0.5, 0.5, 0.5 , 1.0));
        Renderer::getInstance()->beginDraw(glm::mat4(1), testSettings);
        Renderer::getInstance()->draw(testVertexArray, testShader);
        Renderer::getInstance()->endDraw();
        textureTest.unbind();
        testShader.unbind();
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

    void TestScene::initData() {
    }
}