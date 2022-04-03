#include "EditorScene.h"

#include "core/KeyCodes.h"
#include "core/MouseCodes.h"


namespace  DEngine{
    EditorScene::EditorScene(std::shared_ptr<Window> _windowPtr): Scene("EditorScene"), windowPtr(_windowPtr){

    }
    EditorScene::~EditorScene(){

    }
    void EditorScene::attach() {
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;


        ImGui::StyleColorsDark();
        ImGuiStyle& style = ImGui::GetStyle();

        ImGui_ImplGlfw_InitForOpenGL(windowPtr.get()->getGLFWWindow(), true);
        ImGui_ImplOpenGL3_Init("#version 410");

    }

    void EditorScene::detach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void EditorScene::input(Event &e) {

    }
    void EditorScene::update() {
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
    }

    void EditorScene::beginGUI() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }
    void EditorScene::endGUI() {
        ImGui::EndFrame();
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}