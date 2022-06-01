#include "GameScene.h"
#include "input/Input.h"
#include "core/Engine.h"
#include "core/Random.h"
#include "physics/ColisionDetection.h"
#include "primitives/Cube.h"

namespace DEngine{

    void GameScene::attach(){
        //INITING STUFF
        DENGINE_WARN("HEY GAME SCENE!");
        isButtonPressed = false;
        projection  = glm::perspective(glm::radians(45.0f), (float)1600/900, 0.01f, 100.0f);
        glm::vec3 cameraPos(0.0f,0.0f,1.0f);
        view = glm::lookAt(cameraPos,
                           cameraPos+glm::vec3(0.0f, 0.0f, -1.0f),
                           glm::vec3(0.0f, 1.0f, 0.0f));

        model = glm::mat4(1.0f);
        playerview = glm::mat4(1.0f);

        debugCube =  std::make_shared<Cube>();
        //MODEL LOADING
        planeModel = std::make_shared<Model>(PATH_MODELS+"plane/plane.obj",true);
        playerShader =  std::make_shared<Shader>(PATH_SHADERS+ "TestVertexShader.glsl",PATH_SHADERS+ "TestFragmentShader.glsl");
        debugColisionShader = std::make_shared<Shader>(PATH_SHADERS_GAME +"ground/VertexShader.glsl", PATH_SHADERS_GAME+ "ground/FragmentShader.glsl");
        bombModel = std::make_shared<Model>(PATH_MODELS_GAME+ "bomb/bomb.obj",true);

        cubeModel = std::make_shared<Model>(PATH_MODELS_GAME +"cube/cube.obj", true);

        treeModel =  std::make_shared<Model>(PATH_MODELS_GAME +"tree/tree.obj", true);
        rockModel = std::make_shared<Model>(PATH_MODELS_GAME +"rock/rock.obj", true);
        kremlModel = std::make_shared<Model>(PATH_MODELS_GAME +"kreml/kreml.obj", true);
        //MODEL LOADING

        entities.emplace_back(Engine::entitySystemManager.createEntity()); //0
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //1
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //2

        for(int i=0;i<1000;i++){
            entities.emplace_back(Engine::entitySystemManager.createEntity());
        }
        for(int i=0;i<1000;i++){
            entities.emplace_back(Engine::entitySystemManager.createEntity());
        }
        // LAST 2003
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //2003
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //2004
        entities.emplace_back(Engine::entitySystemManager.createEntity()); //2005
        //PLAYER
        TagComponent playerTagComp;
        playerTagComp.tag = "PLAYER";
        Engine::entitySystemManager.addComponent(entities[0],playerTagComp);
        TransformComponent playerTransformComp;
        playerTransformComp.transform = glm::translate(glm::mat4(1), glm::vec3(0.0f,5.0f,125.0f));
        //playerTransformComp.transform =  glm::rotate(playerTransformComp.transform,glm::radians(270.f), glm::vec3(0.0f,1.0f,0.0f));
        Engine::entitySystemManager.addComponent(entities[0],playerTransformComp);
        MeshComponent playerMeshComp;
        playerMeshComp.meshes = planeModel->meshes;
        playerMeshComp.textures= planeModel->textures;
        Engine::entitySystemManager.addComponent(entities[0], playerMeshComp);

        BoxCollider playerCollider(glm::vec3(playerTransformComp.transform[3]),glm::vec3(1.0f,1.0f,1.0f));
        playerCollider.debugCube = debugCube;
        Engine::entitySystemManager.addComponent(entities[0], playerCollider);
        //BoxCollider(const glm::vec3& _min, const glm::vec3& _max )
        //PLAYER

        TransformComponent testCubeTransformComp;
        testCubeTransformComp.transform = glm::mat4(1.0f);
        testCubeTransformComp.transform =  glm::translate(testCubeTransformComp.transform, glm::vec3(0.0f,3.0f,125.0f));
        testCubeTransformComp.transform =  glm::scale(testCubeTransformComp.transform, glm::vec3(0.25f,0.25f,0.5f));
        Engine::entitySystemManager.addComponent(entities[1],testCubeTransformComp);
        MeshComponent testCubeMeshComp;
        testCubeMeshComp.meshes = bombModel->meshes;
        testCubeMeshComp.textures = bombModel->textures;
        Engine::entitySystemManager.addComponent(entities[1], testCubeMeshComp);


        TransformComponent groundCubeTransformComp;
        groundCubeTransformComp.transform = glm::mat4(1.0f);
        groundCubeTransformComp.transform =  glm::translate(groundCubeTransformComp.transform, glm::vec3(0.0f,-5.0f,-100.0f));
        groundCubeTransformComp.transform =  glm::scale(groundCubeTransformComp.transform, glm::vec3(50.0f,0.0f,200.0f));
        Engine::entitySystemManager.addComponent(entities[2],groundCubeTransformComp);
        MeshComponent groundCubeMeshComp;
        groundCubeMeshComp.meshes = cubeModel->meshes;
        groundCubeMeshComp.textures = cubeModel->textures;
        Engine::entitySystemManager.addComponent(entities[2], groundCubeMeshComp);

        BoxCollider groundCollider(glm::vec3(groundCubeTransformComp.transform[3]),glm::vec3(50.0f,0.0,200.0f));
        groundCollider.debugCube = debugCube;
        Engine::entitySystemManager.addComponent(entities[2], groundCollider);


        int startTreeIndex = 3;
        for(int i=0;i<1000;i++){
            TransformComponent treeTransformComp;
            treeTransformComp.transform = glm::mat4(1.0f);
            treeTransformComp.transform =  glm::translate(treeTransformComp.transform, glm::vec3(Random::randomFloat(-50.0f,50.0f),-5.0f,Random::randomFloat(-300.0f,100.0f)));
            Engine::entitySystemManager.addComponent(entities[startTreeIndex+i],treeTransformComp);
            MeshComponent treeMeshComp;
            treeMeshComp.meshes = treeModel->meshes;
            treeMeshComp.textures = treeModel->textures;
            Engine::entitySystemManager.addComponent(entities[startTreeIndex+i], treeMeshComp);
        }
        int startRockIndex = 1003;
        int endRockIndex = startRockIndex+1000;
        for(int i=startRockIndex;i<endRockIndex;i++){
            TransformComponent rockTransformComp;
            rockTransformComp.transform = glm::mat4(1.0f);
            rockTransformComp.transform =  glm::translate(rockTransformComp.transform,glm::vec3(Random::randomFloat(-50.0f,50.0f),-5.0f,Random::randomFloat(-300.0f,100.0f)));
            Engine::entitySystemManager.addComponent(entities[i],rockTransformComp);
            MeshComponent rockMeshComp;
            rockMeshComp.meshes = rockModel->meshes;
           rockMeshComp.textures = rockModel->textures;
            Engine::entitySystemManager.addComponent(entities[i], rockMeshComp);
        }

        TransformComponent kremlTransformComp;
        kremlTransformComp.transform = glm::mat4(1.0f);
        kremlTransformComp.transform =  glm::translate(kremlTransformComp.transform,glm::vec3(0.0f,-5.0f,0.0f));
        kremlTransformComp.transform =  glm::scale(kremlTransformComp.transform, glm::vec3(0.25f,0.25f,0.25f));
        Engine::entitySystemManager.addComponent(entities[2003],kremlTransformComp);
        MeshComponent kremlMeshComp;
        kremlMeshComp.meshes = kremlModel->meshes;
        kremlMeshComp.textures = kremlModel->textures;
        Engine::entitySystemManager.addComponent(entities[2003], kremlMeshComp);

        BoxCollider kremlCollider(glm::vec3(kremlTransformComp.transform[3]),glm::vec3(1.0f,5.0f,1.0f));
        kremlCollider.debugCube = debugCube;
        Engine::entitySystemManager.addComponent(entities[2003], kremlCollider);



        TransformComponent bombLeftTransformComp;
        bombLeftTransformComp.transform = glm::mat4(1.0f);
        bombLeftTransformComp.transform =  glm::translate(bombLeftTransformComp.transform, glm::vec3(0.0f,3.0f,125.0f));
        bombLeftTransformComp.transform =  glm::scale(bombLeftTransformComp.transform, glm::vec3(0.25f,0.25f,0.5f));
        Engine::entitySystemManager.addComponent(entities[2004],bombLeftTransformComp);
        MeshComponent bombLeftMeshComp;
        bombLeftMeshComp.meshes = bombModel->meshes;
        bombLeftMeshComp.textures = bombModel->textures;
        Engine::entitySystemManager.addComponent(entities[2004], bombLeftMeshComp);

        BoxCollider bombLeftCollider(glm::vec3(bombLeftTransformComp.transform[3]),glm::vec3(0.25f,0.25f,0.25f));
        bombLeftCollider.debugCube = debugCube;
        Engine::entitySystemManager.addComponent(entities[2004], bombLeftCollider);

        TransformComponent bombRightTransformComp;
        bombRightTransformComp.transform = glm::mat4(1.0f);
        bombRightTransformComp.transform =  glm::translate(bombRightTransformComp.transform, glm::vec3(0.0f,3.0f,125.0f));
        bombRightTransformComp.transform =  glm::scale(bombRightTransformComp.transform, glm::vec3(0.25f,0.25f,0.5f));
        Engine::entitySystemManager.addComponent(entities[2005],bombRightTransformComp);
        MeshComponent bombRightMeshComp;
        bombRightMeshComp.meshes = bombModel->meshes;
        bombRightMeshComp.textures = bombModel->textures;
        Engine::entitySystemManager.addComponent(entities[2005], bombLeftMeshComp);

        BoxCollider bombRightCollider(glm::vec3(bombRightTransformComp.transform[3]),glm::vec3(0.25f,0.25f,0.25f));
        bombRightCollider.debugCube = debugCube;
        Engine::entitySystemManager.addComponent(entities[2005], bombRightCollider);


    }
    void GameScene::input(Event& e){
        EventDispatcher dispatcher(e);
        dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(GameScene::windowClose));
        dispatcher.dispatch<MouseButtonPressed>(BIND_EVENT_FUNCTION(GameScene::onMousePressed));
        dispatcher.dispatch<MouseButtonReleased>(BIND_EVENT_FUNCTION(GameScene::onMouseReleased));
        dispatcher.dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(GameScene::onMouseMovedEvent));

        //auto [x,y] = Input::getMousePosition();
        //DENGINE_INFO("X {}  Y {}", x, y);
    }
    void GameScene::update(float dt){

        if(Input::isKeyPressed(GLFW_KEY_W)){
                    maxPlaneAngle += glm::vec3(1.0f, 0.0f, 0.0f);
                    Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform = glm::rotate(
                            Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,
                            glm::radians(rotationSpeed * dt), glm::vec3(1.0f, 0.0f, 0.0f));
        }else if(Input::isKeyPressed(GLFW_KEY_S)){
                    maxPlaneAngle += glm::vec3(-1.0f , 0.0f, 0.0f);
                    Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform = glm::rotate(
                            Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,
                            glm::radians(-rotationSpeed * dt), glm::vec3(1.0f, 0.0f, 0.0f));
        }else if(Input::isKeyPressed(GLFW_KEY_A)){
                if(maxPlaneAngle[2]<=(10.0f)) {
                    dir = glm::vec3(-1.0f * (rotationSpeed / 10.0f), 0.0f, 0.0f);
                }
                    maxPlaneAngle += glm::vec3(0.0f, 0.0f, 1.0f);
                    Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform = glm::rotate(
                            Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,
                            glm::radians(rotationSpeed * dt), glm::vec3(0.0f, 0.0f, 1.0f));

        }else if(Input::isKeyPressed(GLFW_KEY_D)){
            if(maxPlaneAngle[2]>=(-10.0f)) {
                dir = glm::vec3(1.0f * (rotationSpeed / 10.0f), 0.0f, 0.0f);
            }
                        maxPlaneAngle += glm::vec3(0.0f, 0.0f, -1.0f);
                        Engine::entitySystemManager.getComponent<TransformComponent>(
                                entities[0]).transform = glm::rotate(
                                Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,
                                glm::radians(-rotationSpeed * dt), glm::vec3(0.0f, 0.0f, 1.0f));

        }

        if((maxPlaneAngle[2] >= -3.0f) &&  (maxPlaneAngle[2] <= 3.0f) ){
            dir = glm::vec3(0.0f,0.0f,0.0f);
        }

        DENGINE_WARN("angle  {}, angle  {}, angle  {}",maxPlaneAngle[0],maxPlaneAngle[1], maxPlaneAngle[2]);

        DENGINE_ERROR("{},{},{}", camera.position[0],camera.position[1], camera.position[2]);
        currentDeltaTime = dt;

        DENGINE_ERROR("SPEEED {}", dir[0]*dt);
        Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform =
                glm::translate( Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform, glm::vec3(dir[0]*dt,0.0f,(-planeSpeed)*dt));


        if((maxPlaneAngle[0]>=90.0f) && (!switched)){
            backUpTransform =  Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform;

            camera.RotateY(-1.0f);
            switched = true;
            isFowardCamera = false;
            maxPlaneAngle[0]=0.0f;
        }
        else if(((maxPlaneAngle[0]<=-90.0f) || (maxPlaneAngle[0]>=260.0f)) && (switched) ){
            DENGINE_ERROR("ROTATED BACK!");
            camera.RotateY(1.0f);
            switched = false;
            isFowardCamera = true;
            maxPlaneAngle[0]=0.0f;
        }

        if(switched && (maxPlaneAngle[0]>=80.0f && maxPlaneAngle[0]<=130.0f)){
            maxPlaneAngle[2]=0.0f;
        }
    //}else if(maxPlaneAngle[0]<3.0f && (isFowardCamera)){

        if(!isFowardCamera){
            DENGINE_ERROR("NOT BASE ROTATION!!!");
            cameraPos =
                    glm::vec3(Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform[3]) +
                    glm::vec3(0.0f, 1.0f, -7.0f);
        }else if(isFowardCamera){
            DENGINE_ERROR("BASE ROTATION!!!");
            cameraPos =
                    glm::vec3(Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform[3]) +
                    glm::vec3(0.0f, 1.0f, 7.0f);
        }


        cameraTarget = glm::vec3(
                Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform[3]);





        playerview = camera.Get3RDPersonViewMatrix(cameraPos, cameraTarget);

        Engine::entitySystemManager.getComponent<BoxCollider>(entities[0]).center = glm::vec3(Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform[3]);


        if(ColisionDetection::collideAABBtoAABB( Engine::entitySystemManager.getComponent<BoxCollider>(entities[0]), Engine::entitySystemManager.getComponent<BoxCollider>(entities[2]))){
            Renderer::getInstance()->clear(glm::vec4(0.886f, 0.156f, 0.156f, 1.0f));
            Engine::sceneManager.popScene();
            return;
        }

        if(ColisionDetection::collideAABBtoAABB( Engine::entitySystemManager.getComponent<BoxCollider>(entities[0]), Engine::entitySystemManager.getComponent<BoxCollider>(entities[2003]))){
            Renderer::getInstance()->clear(glm::vec4(0.886f, 0.156f, 0.156f, 1.0f));
            Engine::sceneManager.popScene();
            return;
        }


        DrawCallSettings  testSettings;
        testSettings.enableBlendingFlag=true;
        testSettings.enableDepthTestFlag=true;

        Renderer::getInstance()->clear(glm::vec4(0.1f, 0.1f, 0.1f, 1.0));
        Renderer::getInstance()->beginDraw(glm::mat4(1), testSettings);
        //BOMBS
        if(!bombLeftUsed) {
            playerShader->bind();
            playerShader->setUniformMat4f("projection", projection);
            playerShader->setUniformMat4f("view", playerview);
            Engine::entitySystemManager.getComponent<TransformComponent>(
                    entities[2004]).transform = Engine::entitySystemManager.getComponent<TransformComponent>(
                    entities[0]).transform;
            Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform = glm::scale(
                    Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform,
                    glm::vec3(0.20f, 0.20f, 0.25f));
            playerShader->setUniformMat4f("model", glm::translate(
                    Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform,
                    glm::vec3(-1.5f, -1.0f, 0.0f)));
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[2004]),
                                          *playerShader);
        }else{
            playerShader->bind();
            playerShader->setUniformMat4f("projection", projection);
            playerShader->setUniformMat4f("view", playerview);
            if(!leftOnce) {
                Engine::entitySystemManager.getComponent<TransformComponent>(
                        entities[2004]).transform = Engine::entitySystemManager.getComponent<TransformComponent>(
                        entities[0]).transform;
                Engine::entitySystemManager.getComponent<TransformComponent>(
                        entities[2004]).transform = Engine::entitySystemManager.getComponent<TransformComponent>(
                        entities[0]).transform;
                Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform = glm::scale(
                        Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform,
                        glm::vec3(0.20f, 0.20f, 0.25f));
                leftOnce = true;
            }

            Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform = glm::translate(  Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform,bombSpeed*dt);
            playerShader->setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[2004]),
                                          *playerShader);

        }

        if(!bombRightUsed){
            playerShader->bind();
            playerShader->setUniformMat4f("projection", projection);
            playerShader->setUniformMat4f("view", playerview);
            Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform =Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform;
            Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform = glm::scale(Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform,glm::vec3(0.20f,0.20f,0.25f));
            playerShader->setUniformMat4f("model", glm::translate(  Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform,glm::vec3(1.5f,-1.0f,0.0f)));
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[2005]), *playerShader);
        }else{
            playerShader->bind();
            playerShader->setUniformMat4f("projection", projection);
            playerShader->setUniformMat4f("view", playerview);
            if(!rightOnce) {
                Engine::entitySystemManager.getComponent<TransformComponent>(
                        entities[2005]).transform = Engine::entitySystemManager.getComponent<TransformComponent>(
                        entities[0]).transform;
                Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform = glm::scale(
                        Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform,
                        glm::vec3(0.20f, 0.20f, 0.25f));
                Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform = glm::translate(
                        Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform,
                        glm::vec3(1.5f, -1.0f, 0.0f));
                rightOnce = true;
            }

            Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform = glm::translate(  Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform,bombSpeed*dt);
            playerShader->setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[2005]), *playerShader);

        }





        if(isDebug) {
            debugColisionShader->bind();
            debugColisionShader->setUniformMat4f("projection", projection);
            debugColisionShader->setUniformMat4f("view", playerview);
            glm::mat4 debugTransform = glm::mat4(1);
            debugColisionShader->setUniformMat4f("model", glm::translate(debugTransform,
                                                                         Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                                 entities[0]).center) *
                                                          glm::scale(debugTransform,
                                                                     Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                             entities[0]).extents));
            debugColisionShader->setUniformVec4f("u_Color", glm::vec4(0.886f, 0.156f, 0.156f, 1.0f));
            Renderer::getInstance()->drawDebug(
                    *Engine::entitySystemManager.getComponent<BoxCollider>(entities[0]).debugCube,
                    *debugColisionShader);
        }

        if(isDebug) {
            debugColisionShader->bind();
            debugColisionShader->setUniformMat4f("projection", projection);
            debugColisionShader->setUniformMat4f("view", playerview);
            glm::mat4 debugTransform = glm::mat4(1);
            debugColisionShader->setUniformMat4f("model", glm::translate(debugTransform,
                                                                         Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                                 entities[2]).center) *
                                                          glm::scale(debugTransform,
                                                                     Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                             entities[2]).extents));
            debugColisionShader->setUniformVec4f("u_Color", glm::vec4(0.886f, 0.156f, 0.156f, 1.0f));
            Renderer::getInstance()->drawDebug(
                    *Engine::entitySystemManager.getComponent<BoxCollider>(entities[2]).debugCube,
                    *debugColisionShader);
        }

        if(isDebug) {
            debugColisionShader->bind();
            debugColisionShader->setUniformMat4f("projection", projection);
            debugColisionShader->setUniformMat4f("view", playerview);
            glm::mat4 debugTransform = glm::mat4(1);
            debugColisionShader->setUniformMat4f("model", glm::translate(debugTransform,
                                                                         Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                                 entities[2003]).center) *
                                                          glm::scale(debugTransform,
                                                                     Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                             entities[2003]).extents));
            debugColisionShader->setUniformVec4f("u_Color", glm::vec4(0.886f, 0.156f, 0.156f, 1.0f));
            Renderer::getInstance()->drawDebug(
                    *Engine::entitySystemManager.getComponent<BoxCollider>(entities[2003]).debugCube,
                    *debugColisionShader);
        }

        //BOMBS

        Engine::entitySystemManager.getComponent<BoxCollider>(entities[2004]).center = glm::translate(  Engine::entitySystemManager.getComponent<TransformComponent>(entities[2004]).transform,glm::vec3(-1.5f,-1.0f,0.0f))[3];
        Engine::entitySystemManager.getComponent<BoxCollider>(entities[2005]).center = glm::translate(  Engine::entitySystemManager.getComponent<TransformComponent>(entities[2005]).transform,glm::vec3(1.5f,-1.0f,0.0f))[3];
        if(isDebug) {
            debugColisionShader->bind();
            debugColisionShader->setUniformMat4f("projection", projection);
            debugColisionShader->setUniformMat4f("view", playerview);
            glm::mat4 debugTransform = glm::mat4(1);
            debugColisionShader->setUniformMat4f("model", glm::translate(debugTransform,
                                                                         Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                                 entities[2004]).center) *
                                                          glm::scale(debugTransform,
                                                                     Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                             entities[2004]).extents));
            debugColisionShader->setUniformVec4f("u_Color", glm::vec4(0.886f, 0.156f, 0.156f, 1.0f));
            Renderer::getInstance()->drawDebug(
                    *Engine::entitySystemManager.getComponent<BoxCollider>(entities[2004]).debugCube,
                    *debugColisionShader);
        }

        if(isDebug) {
            debugColisionShader->bind();
            debugColisionShader->setUniformMat4f("projection", projection);
            debugColisionShader->setUniformMat4f("view", playerview);
            glm::mat4 debugTransform = glm::mat4(1);
            debugColisionShader->setUniformMat4f("model", glm::translate(debugTransform,
                                                                         Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                                 entities[2005]).center) *
                                                          glm::scale(debugTransform,
                                                                     Engine::entitySystemManager.getComponent<BoxCollider>(
                                                                             entities[2005]).extents) );
            debugColisionShader->setUniformVec4f("u_Color", glm::vec4(0.886f, 0.156f, 0.156f, 1.0f));
            Renderer::getInstance()->drawDebug(
                    *Engine::entitySystemManager.getComponent<BoxCollider>(entities[2005]).debugCube,
                    *debugColisionShader);
        }
        //BOMBS


        playerShader->bind();
        playerShader->setUniformMat4f("projection", projection);

        playerShader->setUniformMat4f("view",playerview);
        //playerShader->setUniformMat4f("model", glm::translate(glm::translate(glm::mat4(1), glm::vec3(0.0f,-1.0f,-7.0f)), camera.position));
        playerShader->setUniformMat4f("model",glm::translate(  Engine::entitySystemManager.getComponent<TransformComponent>(entities[0]).transform,camera.position));
        Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[0]), *playerShader);

        playerShader->bind();
        playerShader->setUniformMat4f("projection", projection);
        playerShader->setUniformMat4f("view", playerview);
        playerShader->setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[2]).transform);
        Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[2]), *playerShader);

        int startTreeIndex =3;
        for(int i=0;i<1000;i++){
            playerShader->bind();
            playerShader->setUniformMat4f("projection", projection);
            playerShader->setUniformMat4f("view", playerview);
            playerShader->setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[startTreeIndex+i]).transform);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[startTreeIndex+i]), *playerShader);
        }

        int startRockIndex = 1003;
        int endRockIndex = startRockIndex+1000;
        for(int i=startRockIndex;i<endRockIndex;i++) {
            playerShader->bind();
            playerShader->setUniformMat4f("projection", projection);
            playerShader->setUniformMat4f("view", playerview);
            playerShader->setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[i]).transform);
            Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[i]), *playerShader);
        }

        playerShader->bind();
        playerShader->setUniformMat4f("projection", projection);
        playerShader->setUniformMat4f("view", playerview);
        playerShader->setUniformMat4f("model", Engine::entitySystemManager.getComponent<TransformComponent>(entities[2003]).transform);
        Renderer::getInstance()->draw(Engine::entitySystemManager.getComponent<MeshComponent>(entities[2003]), *playerShader);
        Renderer::getInstance()->endDraw();




        //POP SCENE IN PROPER WAY DONT REMOVE!
        //if(timeCounter>5){
        //    Renderer::getInstance()->clear();
        //    Engine::sceneManager.popScene();
        //    return;
        //}
    }


    void GameScene::detach(){
        //DELETING STUFF
        for(auto it = entities.begin();it<entities.end();it++){
            Engine::entitySystemManager.destroyEntity(*it);
        }
    }

    bool GameScene::onKeyPressedInput(KeyPressedEvent& e){
        return true;
    }
    bool GameScene::windowClose(WindowCloseEvent& e){
        Engine::isRunning = false;
        return true;
    }
    bool GameScene::onMousePressed(MouseButtonPressed& e){
        if(e.getMouseCode() ==ButtonLeft){
            if(!bombLeftUsed){
                bombLeftUsed= true;
            }
        }
        if(e.getMouseCode() == ButtonRight){
            if(!bombRightUsed){
                bombRightUsed =true;
            }
        }
        return true;
    }
    bool GameScene::onMouseReleased(MouseButtonReleased& e){
        return true;
    }
    bool GameScene::onMouseMovedEvent(MouseMovedEvent& e){
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
}