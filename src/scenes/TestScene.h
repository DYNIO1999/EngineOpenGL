#ifndef DENGINE_TESTSCENE_H
#define DENGINE_TESTSCENE_H

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

namespace DEngine {
    class TestScene : public Scene {
    public:
        TestScene(std::string name, std::shared_ptr<Window> _windowPtr): Scene(name),
                                     testShader(PATH_SHADERS+ "TestVertexShader.glsl",PATH_SHADERS+ "TestFragmentShader.glsl")
                                     ,textureTest(PATH_TEXTURES + "particles/water.png")
                                     ,windowPtr(_windowPtr)
                                     ,smokeShader(PATH_SHADERS+"particles/smoke/SmokeVertexShader.glsl",PATH_SHADERS+"particles/smoke/SmokeFragmentShader.glsl")
        {
            initData();
        };
        ~TestScene();
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
        Shader smokeShader;
        //Shader particleComputeShader;
        //Shader particleShader;
        Texture textureTest;
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




        //TEST SMOKE PARTICLES
        glm::vec3 emitterDir{0,1,0};
        int totalParticles;
        std::shared_ptr<Shader> computeShader;
        std::shared_ptr<Shader> smokeParticleShader;
        uint particlesVao;
        uint posBuf;
        uint velBuf;
        uint age;
        //TEST SMOKE PARTICLES


        //glm::ivec3 nParticles;
        //uint totalParticles;
        //float time, deltaT, speed, angle;
        //uint particlesVao;
        //uint bhVao, bhBuf;  // black hole VAO and buffer
        //glm::vec4 bh1, bh2;
    };
}
#endif
