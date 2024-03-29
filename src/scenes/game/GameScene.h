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
        bool wonScene{false};
        bool lostScene{false};
        double time{0.0f};
        bool wonGame{false};
        bool lostGame{false};
        bool isDebug{false};
        bool bombLeftUsed{false};
        bool bombRightUsed{false};
        bool leftOnce{false};
        bool rightOnce{false};
        float planeSpeed{10.0f};

        int usedBombs{0};
        glm::vec3 bombSpeed{0.0f,-30.0f,-15.0f};
        glm::vec3 cameraTarget;
        glm::vec3 cameraPos;


        std::shared_ptr<Window> windowPtr;
        glm::vec3 dir{0.0f,0.0f,0.0f};
        float cameraSpeed{10.0f};
        Camera camera;
        float currentDeltaTime;
        glm::mat4 model, view, projection;
        glm::mat4 playerview;
        std::vector<Entity> entities;


        std::shared_ptr<Mesh> quadMesh;

        std::shared_ptr<Shader> playerShader;

        std::shared_ptr<Texture> wonTexture;
        std::shared_ptr<Texture> lostTexture;

        std::shared_ptr<Shader> debugColisionShader;
        std::shared_ptr<Mesh> debugCube;
        std::shared_ptr<Model> rockModel;
        std::shared_ptr<Model> treeModel;
        std::shared_ptr<Model> planeModel;
        std::shared_ptr<Model> cubeModel;
        std::shared_ptr<Model> bombModel;
        std::shared_ptr<Model> kremlModel;

        glm::mat4 backUpTransform;
        bool isFowardCamera{true};
        glm::vec3 maxPlaneAngle{0.0f,0.0f,0.0f};
        bool switched = false;
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
