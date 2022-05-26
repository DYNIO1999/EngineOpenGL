#ifndef DENGINE_GAMESCENE_H
#define DENGINE_GAMESCENE_H
#include "ecs/EntitySystemManager.h"


#include "renderer/Renderer.h"
#include "core/SceneManager.h"
#include "core/Window.h"
#include "renderer/Model.h"
#include "core/Camera.h"


namespace DEngine {
    class GameScene :public Scene{

    public:
        GameScene(std::string _name, std::shared_ptr<Window> _windowPtr) : Scene(_name), windowPtr(_windowPtr)
        {

        };
        ~GameScene(){

        }
        void attach()override;
        void initScene() override{

        };

        void input(Event& e) override;
        void update(float dt) override;
        void detach() override;


    private:
        std::shared_ptr<Window> windowPtr;
        glm::vec3 dir{0.0f,0.0f,0.0f};
        float cameraSpeed{10.0f};
        Camera camera;
        float currentDeltaTime;
        glm::mat4 model, view, projection;
        glm::mat4 playerview;
        std::vector<Entity> entities;
        std::shared_ptr<Shader> playerShader;
        std::shared_ptr<Model> planeModel;
        std::shared_ptr<Model> cubeModel;
        std::shared_ptr<Model> bombModel;


        glm::vec3 maxPlaneAngle{0.0f,0.0f,0.0f};

        float rotationSpeed{50.0f};
        bool isButtonPressed;
        bool onKeyPressedInput(KeyPressedEvent& e);
        bool windowClose(WindowCloseEvent& e);
        bool onMousePressed(MouseButtonPressed& e);
        bool onMouseReleased(MouseButtonReleased& e);
        bool onMouseMovedEvent(MouseMovedEvent& e);
    };
}
#endif
