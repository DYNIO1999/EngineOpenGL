#include "WaveSurfaceScene.h"
#include <random>
#include <cmath>
#include "core/Engine.h"
namespace DEngine{

    void WaveSurfaceScene::initScene() {
       glm::mat4 current = glm::mat4(1);
        current = glm::translate(current,glm::vec3(0,0, -1));
        hair.push_back(current);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);
    }
    void WaveSurfaceScene::input(Event &e) {
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(WaveSurfaceScene::onKeyPressedInput));
    }
    void WaveSurfaceScene::update() {




        DrawCallSettings  testSettings;


        projection  = glm::perspective(glm::radians(camera.zoom), (float)1600/900, 0.1f, 100.0f);


        glm::vec3 cameraPos(0.0f,0.0f,3.0f);
        view = glm::lookAt(cameraPos,
                           cameraPos+glm::vec3(0.0f, 0.0f, -1.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));

        model = glm::mat4(1.0f);



        std::vector<float> vertices{-1.0f, -1.0f, -1.0f,
                                    -0.5f, 1.0f,-1.0f,
                                    0.5f, -1.0f,-1.0f,
                                    1.0f, 1.0f,-1.0f,

                                    -1.0f, -1.0f, -0.66f,
                                    -0.5f, 1.0f,-0.66f,
                                    0.5f, -1.0f,-0.66f,
                                    1.0f, 1.0f,-0.66f,


                                    -1.0f, -1.0f, -0.33f,
                                    -0.5f, 1.0f,-0.33f,
                                    0.5f, -1.0f,-0.33f,
                                    1.0f, 1.0f,-0.33f,

                                    -1.0f, -1.0f, 0.0,
                                    -0.5f, 1.0f,0.0,
                                    0.5f, -1.0f,0.0,
                                    1.0f, 1.0f,0.0
        };
        VertexBuffer vbo{vertices.data(), static_cast<unsigned  int>(sizeof(float) * vertices.size())};
        VertexBufferLayout vbl;
        vbl.push<float>(3);
        VertexArray vao;
        vao.addBuffer(vbo, vbl);
        vao.bind();
        glPatchParameteri( GL_PATCH_VERTICES, 16);



      //  Renderer::getInstance()->beginDraw(glm::mat4(1), testSettings);
       // Renderer::getInstance()->clear(glm::vec4(0.5, 0.5, 0.5 , 1.0));
        float timeValue = glfwGetTime();
        float yValue = sin(timeValue) / 2.0f + 0.5f;
        testShader.bind();
        view = camera.GetViewMatrix();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for(size_t i = 0; i<hair.size();i++){
            testShader.setUniform1i("TessLevel", 16);
            testShader.setUniform4f("LineColor", 1.0f,1.0f,0.5f,1.0f);
            testShader.setUniformMat4f("model", hair[i]);
            testShader.setUniformMat4f("view",view);
            testShader.setUniformMat4f("projection",projection);
            glDrawArrays(GL_PATCHES, 0, 16);
        }

       // for (int i = 0; i < 100 ; ++i) {
       //     testShader.setUniform1i("NumSegments", 50);
       //     testShader.setUniform1i("NumStrips", 1);
       //     testShader.setUniform4f("LineColor", 0.0f,1.0f,0.5f,1.0f);
       //     testShader.setUniform1f("sin", yValue);
       //     testShader.setUniformMat4f("model", hair[i]);
       //     testShader.setUniformMat4f("view",view);
       //     testShader.setUniformMat4f("projection",projection);
       //     glDrawArrays(GL_PATCHES, 0, 4);
       // }
       // //testShader.setUniform1i("NumSegments", 50);
        //testShader.setUniform1i("NumStrips", 1);
        //testShader.setUniform4f("LineColor", 0.0f,1.0f,0.5f,1.0f);
        //testShader.setUniform1f("sin", yValue);
        //testShader.setUniformMat4f("model", model2);
        //testShader.setUniformMat4f("view",view);
        //testShader.setUniformMat4f("projection",projection);
        //glDrawArrays(GL_PATCHES, 0, 4);
        //Renderer::getInstance()->draw(testVertexArray, testShader);
        //Renderer::getInstance()->endDraw();

    }
    bool WaveSurfaceScene::onKeyPressedInput(KeyPressedEvent& e){

        switch (e.getKeyCode()) {
            case W:
                camera.processKeyboard(Camera_Movement::FORWARD_CAMERA_MOVE, 0.1);
                std::cout<<"test"<<'\n';
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

    }

    bool WaveSurfaceScene::windowClose(WindowCloseEvent &e) {
        return  true;
    }
}