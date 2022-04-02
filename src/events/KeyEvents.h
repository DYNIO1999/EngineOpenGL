#ifndef DENGINE_KEYEVENTS_H
#define DENGINE_KEYEVENTS_H

#include "Event.h"
#include "core/KeyCodes.h"

namespace DEngine{
    class KeyEvent : public Event{

    public:
        KeyCode getKeyCode() const { return keyCode;}

    protected:
        KeyEvent(KeyCode _code):keyCode(_code){

    }
        KeyCode  keyCode;
    };

    class KeyPressedEvent :public KeyEvent{

    public:
        KeyPressedEvent(KeyCode _code,  int _repeatCounter)
                : KeyEvent(_code), repeatCounter(_repeatCounter) {}

        int getRepeatCount() const { return repeatCounter; }

        std::string toString() const override
        {
            std::string temp ="KeyPressedEvent: " + std::to_string(keyCode)+ std::to_string(repeatCounter) + " repeats";
            std::cout<<temp<<'\n';
            return temp;
        }
    private:
        int repeatCounter;
    };



};

#endif