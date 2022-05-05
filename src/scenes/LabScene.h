#ifndef DENGINE_LABSCENE_H
#define DENGINE_LABSCENE_H

#include <unordered_set>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include "imgui_impl_opengl3.h"


#include "core/Scene.h"
#include "renderer/Renderer.h"
#include "ecs/EntitySystemManager.h"

#include "core/Window.h"
#include "renderer/Model.h"
#include "core/Camera.h"

#include "renderer/FrameBuffer.h"

namespace DEngine {
    class LabScene : public Scene {
    public:
        LabScene(std::string name, std::shared_ptr<Window> _windowPtr): Scene(name),
                                     testShader(PATH_SHADERS+ "TestVertexShader.glsl",PATH_SHADERS+ "TestFragmentShader.glsl")
                                     ,multTextureShader(PATH_SHADERS+ "TestVertexShader.glsl", PATH_SHADERS+"MultiTextureFragmentShader.glsl")
                                     ,textureTest(PATH_TEXTURES + "brick.png")
                                     ,firstToMultiTexturing(PATH_TEXTURES + "brick.png")
                                     ,secondToMultiTexturing(PATH_TEXTURES + "multiTexturing/pavement.png")
                                     , maskToMultiTexturing(PATH_TEXTURES + "multiTexturing/path.png")
                                     ,windowPtr(_windowPtr)
        {
            initData();
        };
        ~LabScene();
        void initScene() override{

        }
        void input(Event& e) override;

        void update(float dt) override;
        void detach() override;

        int counter = 0;



        int item_current_idx = 0;
        bool is_selected = false;
        float timeCounter;
        Shader testShader;
        Shader multTextureShader;
        //Shader particleComputeShader;
        //Shader particleShader;
        Texture textureTest;
        Texture firstToMultiTexturing;
        Texture secondToMultiTexturing;
        Texture maskToMultiTexturing;
    private:
        void ImGUITest();
        void initData();

        bool onKeyPressedInput(KeyPressedEvent& e);
        bool windowClose(WindowCloseEvent& e);
        bool isButtonPressed;
        bool onMousePressed(MouseButtonPressed& e);
        bool onMouseReleased(MouseButtonReleased& e);
        bool onMouseMovedEvent(MouseMovedEvent& e);

        float currentDeltaTime;
        Camera camera{glm::vec3(0.0f, 0.0f, 0.3f)};
        std::shared_ptr<Model> testModel;
        std::shared_ptr<Mesh> testMesh;
        std::vector<Entity> entities;
        glm::mat4 model, view, projection;
        std::shared_ptr<Window> windowPtr;

        std::shared_ptr<FrameBuffer> frameBuffer;



        void particlesLab();
        void texturesLab();
        void shadersLab();
        void lightsLab();
        //glm::ivec3 nParticles;
        //uint totalParticles;
        //float time, deltaT, speed, angle;
        //uint particlesVao;
        //uint bhVao, bhBuf;  // black hole VAO and buffer
        //glm::vec4 bh1, bh2;
    };
}
#endif
