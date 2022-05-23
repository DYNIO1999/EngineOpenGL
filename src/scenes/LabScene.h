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
                                     ,firstToMultiTexturing(PATH_TEXTURES + "multiTexturing/snow.png")
                                     ,thirdToMultiTexturing(PATH_TEXTURES + "multiTexturing/pavement.jpg")
                                     ,secondToMultiTexturing(PATH_TEXTURES + "multiTexturing/path.png")
                                     ,multiTexture2Shader(PATH_SHADERS+ "TestVertexShader.glsl", PATH_SHADERS+"MultiTextureSecondFragmentShader.glsl")
                                     ,dengineTexture(PATH_TEXTURES + "DEngine.png")
                                     ,lightSourceShader(PATH_SHADERS + "lightning/light/VertexShader.glsl", PATH_SHADERS+"lightning/light/FragmentShader.glsl")
                                     ,ambientLightShader(PATH_SHADERS + "lightning/ambient/VertexShader.glsl", PATH_SHADERS+"lightning/ambient/FragmentShader.glsl")
                                     ,diffuseLightShader(PATH_SHADERS + "lightning/diffuse/VertexShader.glsl", PATH_SHADERS+"lightning/diffuse/FragmentShader.glsl")
                                     ,specularLightShader(PATH_SHADERS + "lightning/specular/VertexShader.glsl", PATH_SHADERS+"lightning/specular/FragmentShader.glsl")
                                     ,phongLightShader(PATH_SHADERS + "lightning/phong/VertexShader.glsl", PATH_SHADERS+"lightning/phong/FragmentShader.glsl")
                                     ,blinnphongLightShader(PATH_SHADERS + "lightning/blinnphong/VertexShader.glsl", PATH_SHADERS+"lightning/blinnphong/FragmentShader.glsl")
                                     ,toonShader(PATH_SHADERS+"shadersLab/toonshading/VertexShader.glsl", PATH_SHADERS+"shadersLab/toonshading/FragmentShader.glsl")
                                     ,isButtonPressed(false)
                                     ,dirtTexture(PATH_TEXTURES + "dirt.png")
                                     ,dynioLove(PATH_TEXTURES + "dyniolove.png")
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
        Shader multiTexture2Shader;
        //Shader particleComputeShader;
        //Shader particleShader;
        Texture textureTest;
        Texture dengineTexture;
        Texture firstToMultiTexturing;
        Texture secondToMultiTexturing;
        Texture thirdToMultiTexturing;
        Texture dirtTexture;
        Texture dynioLove;

        Shader lightSourceShader;
        Shader ambientLightShader;
        Shader diffuseLightShader;
        Shader specularLightShader;
        Shader phongLightShader;
        Shader blinnphongLightShader;
        Shader toonShader;
        
        glm::vec3 lightSourcePosition;

        glm::vec3 ambientLightColor{0.2f,0.1f,0.6f};
        glm::vec3 objectColor{0.1f, 0.1f, 0.6f};
        float ambientLightIntensity =0.1f;
        float specularLightIntensity = 0.5f;
        int levels = 3;
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
        bool up{true};
        Camera camera{glm::vec3(0.0f, 0.0f, 0.3f)};
        std::shared_ptr<Model> cubeModel;
        std::shared_ptr<Model> sphereModel;
        std::shared_ptr<Model> backpackModel;
        std::shared_ptr<Model> planeModel;

        std::pair<float,float> minMax{0.0f,1.0f};

        std::shared_ptr<Mesh> testMesh;
        std::vector<Entity> entities;
        glm::mat4 model, view, projection;
        std::shared_ptr<Window> windowPtr;

        std::shared_ptr<FrameBuffer> frameBuffer;



        void editorShaderLab();
        void editorLightsLab();
        void particlesLab();
        void texturesLab();
        void shadersLab();
        void lightsLab();


        void modelLoadingLab();
        void enviromentMappingLab();


        float cameraSpeed{10.0f};
    };
}
#endif
