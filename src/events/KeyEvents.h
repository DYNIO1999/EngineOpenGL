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
                : KeyEvent(_code), repeatCounter(_repeatCounter) {

        }

        int getRepeatCount() const { return repeatCounter; }

        std::string getName() const override
        {
            std::string temp ="KeyPressedEvent: " + std::to_string(keyCode)+" "+std::to_string(repeatCounter) + " repeats";
            std::cout<<temp<<'\n';
            return "KeyPressed";
        }
        EventType getEventType() const override {
            return EventType::KeyPressed;
        }
        static EventType getStaticType() { return EventType::KeyPressed;};
    private:
        int repeatCounter;
    };
    class KeyReleasedEvent :public KeyEvent{
    public:
        KeyReleasedEvent(KeyCode _code)
        : KeyEvent(_code){

        }
        std::string getName() const override
        {
            std::string temp ="KeyReleasedEvent: " + std::to_string(keyCode);
            std::cout<<temp<<'\n';
            return "KeyReleased";
        }
        EventType getEventType() const override {
            return EventType::KeyReleased;
        }
        static EventType getStaticType() { return EventType::KeyReleased;};
    private:
    };
};
#endif