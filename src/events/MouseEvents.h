#ifndef DENGINE_MOUSEEVENTS_H
#define DENGINE_MOUSEEVENTS_H
#include "core/MouseCodes.h"
#include "Event.h"

namespace  DEngine {

    //MouseButtonPressed,
    //MouseButtonReleased,
    //MouseMoved,
    //MouseScrolled
    class MouseMovedEvent : public Event{
    public:
        MouseMovedEvent(float _x, float _y):
        x(_x), y(_y){

        }
        float getX() const { return x; }
        float getY() const { return y; }
        std::string getName() const override
        {
            std::string temp ="MouseMoved: " + std::to_string(x)+" "+std::to_string(y);
            std::cout<<temp<<'\n';
            return "MouseMoved";
        }
        EventType getEventType() const override {
            return EventType::MouseMoved;
        }
        static EventType getStaticType() { return EventType::MouseMoved;};
    private:
        float x,y;
    };

    class MouseScrolledEvent : public Event{
    public:
        MouseScrolledEvent(float _x, float _y):
                x(_x), y(_y){

        }
        float getX() const { return x; }
        float getY() const { return y; }
        std::string getName() const override
        {
            std::string temp ="MouseScrolled: " + std::to_string(x)+" "+std::to_string(y);
            std::cout<<temp<<'\n';
            return "MouseScrolled";
        }
        EventType getEventType() const override {
            return EventType::MouseScrolled;
        }
        static EventType getStaticType() { return EventType::MouseScrolled;};
    private:
        float x,y;
    };


    class MouseButtonEvent : public Event{

    public:
        MouseCode getMouseCode() const { return mouseCode;}

    protected:
        MouseButtonEvent(MouseCode _code):mouseCode(_code){

        }
        MouseCode mouseCode;
    };
    class MouseButtonPressed : public  MouseButtonEvent{
    public:
        MouseButtonPressed(MouseCode _code): MouseButtonEvent(_code){

        }
        std::string getName() const override
        {
            std::string temp ="MouseButtonPressed: " + std::to_string(mouseCode);
            std::cout<<temp<<'\n';
            return "MousePressed";
        }
        EventType getEventType() const override {
            return EventType::MouseButtonPressed;
        }
        static EventType getStaticType() { return EventType::MouseButtonPressed;};
    private:
    };

    class MouseButtonReleased : public  MouseButtonEvent{
    public:
        MouseButtonReleased(MouseCode _code): MouseButtonEvent(_code){

        }
        std::string getName() const override
        {
            std::string temp ="MouseButtonReleased: " + std::to_string(mouseCode);
            std::cout<<temp<<'\n';
            return "MouseReleased";
        }
        EventType getEventType() const override {
            return EventType::MouseButtonReleased;
        }
        static EventType getStaticType() { return EventType::MouseButtonReleased;};

    private:
    };

}
#endif