#include "WaveSurfaceScene.h"
#include <random>
#include <cmath>
#include "core/Engine.h"
namespace DEngine{

    void WaveSurfaceScene::initScene() {
       glm::mat4 current = glm::mat4(1);
       glm::mat4 second = glm::mat4(1);
        current = glm::translate(current,glm::vec3(0,0, -1));
        current = glm::rotate(current,glm::radians(-45.0f), glm::vec3(0,0,1));
        current = glm::scale(current,glm::vec3(1,1, 5));
        patch.push_back(current);
        current = glm::translate(current,glm::vec3(0,0, -1.0));
        patch.push_back(current);

        second = glm::translate(second,glm::vec3(2.5,0, -6));
        second = glm::rotate(second,glm::radians(-45.0f), glm::vec3(0,0,1));
        second = glm::scale(second,glm::vec3(1,1, 5));
        patch.push_back(second);
        second = glm::translate(second,glm::vec3(0,0,1));
        patch.push_back(second);

        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    void WaveSurfaceScene::input(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(WaveSurfaceScene::onKeyPressedInput));
        dispatcher.dispatch<MouseButtonPressed>(BIND_EVENT_FUNCTION(WaveSurfaceScene::onMousePressed));
        dispatcher.dispatch<MouseButtonReleased>(BIND_EVENT_FUNCTION(WaveSurfaceScene::onMouseReleased));
        dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(WaveSurfaceScene::onMouseMovedEvent));
    }
    void WaveSurfaceScene::update() {
        int test;

        DrawCallSettings  testSettings;

        projection  = glm::perspective(glm::radians(camera.zoom), (float)1600/900, 0.1f, 100.0f);


        glm::vec3 cameraPos(0.0f,0.0f,3.0f);
        view = glm::lookAt(cameraPos,
                           cameraPos+glm::vec3(0.0f, 0.0f, -1.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));

        model = glm::mat4(1.0f);



        std::vector<float> vertices{-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
                                    -0.5f, 1.0f,-1.0f,0.0f, 1.0f,
                                    0.5f, -1.0f,-1.0f,0.0f, 0.0f,
                                    1.0f, 1.0f,-1.0f,0.0f, 1.0f,

                                    -1.0f, -1.0f, -0.66f,1.0f, 0.0f,
                                    -0.5f, 1.0f,-0.66f,1.0f, 1.0f,
                                    0.5f, -1.0f,-0.66f,1.0f, 0.0f,
                                    1.0f, 1.0f,-0.66f,0.0f, 1.0f,


                                    -1.0f, -1.0f, -0.33f,0.0f, 0.0f,
                                    -0.5f, 1.0f,-0.33f,0.0f, 1.0f,
                                    0.5f, -1.0f,-0.33f,0.0f, 0.0f,
                                    1.0f, 1.0f,-0.33f,0.0f, 1.0f,

                                    -1.0f, -1.0f, 0.0,1.0f, 0.0f,
                                    -0.5f, 1.0f,0.0,1.0f, 1.0f,
                                    0.5f, -1.0f,0.0,1.0f, 0.0f,
                                    1.0f, 1.0f,0.0,0.0f, 1.0f
        };
        VertexBuffer vbo{vertices.data(), static_cast<unsigned  int>(sizeof(float) * vertices.size())};
        VertexBufferLayout vbl;
        vbl.push<float>(3);
        vbl.push<float>(2);
        VertexArray vao;
        vao.addBuffer(vbo, vbl);
        vao.bind();
        glPatchParameteri( GL_PATCH_VERTICES, 16);

        waterTexture.bind();
        testShader.bind();
        testShader.setUniform1i("u_Texture",0);
        view = camera.GetViewMatrix();
        glClearColor(0.6, 0.839, 1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        float timeValueX = glfwGetTime();
        float timeValueY = glfwGetTime();

        for(size_t i = 0; i<patch.size();i++){
            float yValue = sin(timeValueX)   + cos(timeValueY) ;
            testShader.setUniform1i("TessLevel", 16);
            testShader.setUniform1f("sin", yValue);
            testShader.setUniformMat4f("model", patch[i]);
            testShader.setUniformMat4f("view",view);
            testShader.setUniformMat4f("projection",projection);
            glDrawArrays(GL_PATCHES, 0, 16);
        }



        waterTexture.unbind();
        testShader.unbind();
    }
    bool WaveSurfaceScene::onKeyPressedInput(KeyPressedEvent& e){

        switch (e.getKeyCode()) {
            case W:
                camera.processKeyboard(Camera_Movement::FORWARD_CAMERA_MOVE, 0.1);
                break;
            case A:
                camera.processKeyboard(Camera_Movement::LEFT_CAMERA_MOVE, 0.1);
                break;
            case S:
                camera.processKeyboard(Camera_Movement::BACKWARD_CAMERA_MOVE, 0.1);
                break;
            case D:
                camera.processKeyboard(Camera_Movement::RIGHT_CAMERA_MOVE, 0.1);
                break;
        }
        return  true;
    }
    bool WaveSurfaceScene::onMouseMovedEvent(MouseMovedEvent& e){
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


    bool WaveSurfaceScene::onMousePressed(MouseButtonPressed &e) {
        if(e.getMouseCode() ==ButtonLeft){
        isButtonPressed =true;
        }
        if(e.getMouseCode() ==ButtonRight){
            camera.front= glm::vec3(0.0f, 0.0f, -1.0f);
        }
        return true;
    }
    bool WaveSurfaceScene::onMouseReleased(MouseButtonReleased& e){
        if(e.getMouseCode() ==ButtonLeft){
            isButtonPressed = false;
        }
        return true;
    }
    bool WaveSurfaceScene::windowClose(WindowCloseEvent &e) {
        return  true;
    }
}