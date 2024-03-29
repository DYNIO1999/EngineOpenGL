#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H
#include <vector>
#include <string>

#include "events/Event.h"

namespace DEngine {

    class Scene {
        public:
        bool isDisabled;
        Scene(const std::string& _sceneName):isDisabled(false), sceneName(_sceneName){

        }
        virtual void attach(){
            //Scena konstrulowana
        }
        virtual  void initScene(){

        }
        virtual ~Scene(){

        }
        virtual void detach(){
            //Scena usuwana
        }
        virtual void input(Event& e){
            //input
        }
        virtual void update(float dt){
            //zmiana pozycji
            //rysowanie

        }
        const std::string& getSceneName(){return sceneName;}
        protected:
        std::string sceneName;
    };
};
#endif