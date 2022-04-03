#include "TestScene.h"
#include "core/LogManager.h"
#include "core/Engine.h"

namespace DEngine{

    void TestScene::input(Event &e) {
        //std::cout<<e.getName()<<'\n';
    }
    void TestScene::update() {
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
                        is_selected = false;
                    }

                        //ImGui::SetItemDefaultFocus();
                }
                ImGui::EndListBox();
            }
        }
        if (ImGui::CollapsingHeader("Color"))

        {
            ImGui::ColorPicker3("Color",col, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
            //ImGui::SliderFloat("Roughness", NULL, 0.0f, 1.0f);
            //ImGui::SliderFloat("Metallic", NULL, 0.0f, 1.0f);
        }
        ImGui::End();

    }
}