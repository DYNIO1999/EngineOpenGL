#ifndef DENGINE_SCENE_H
#define DENGINE_SCENE_H

#include <vector>
#include "events/Event.h"

namespace DEngine {

    class Scene {
        public:
        Scene(){

        }
        virtual ~Scene(){

        }
        virtual void attach(){
            //Scena konstrulowana
        }
        virtual void detach(){
            //Scena usuwana
        }
        virtual void input(Event& e){
            //input
        }
        virtual void update(){
            //zmiana pozycji
            //rysowanie

        }
        private:
    };
};
#endif