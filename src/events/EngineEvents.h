#ifndef DENGINE_ENGINEEVENTS_H
#define DENGINE_ENGINEEVENTS_H
#include "Event.h"

namespace DEngine {

    class  WindowResizeEvent :public  Event{
    public:
        WindowResizeEvent(int _width,  int _height)
        : width(_width), height(_height) {}

        int getWidth() const { return width; }
        int getHeight() const { return height; }
        std::string getName() const override
        {
            std::string temp ="WindowResized: " + std::to_string(width)+" "+std::to_string(height);
            std::cout<<temp<<'\n';
            return "WindowResized";
        }
        EventType getEventType() const override {
            return EventType::WindowResize;
        }
        static EventType getStaticType() { return EventType::WindowResize;};
    private:
        int width, height;
    };
    
    class  WindowCloseEvent :public  Event{

    public:
        WindowCloseEvent() = default;
        std::string getName() const override
        {
            std::string temp ="WindowCloseEvent: ";
            std::cout<<temp<<'\n';
            return "WindowClose";
        }
        EventType getEventType() const override {
            return EventType::WindowClose;
        }
        static EventType getStaticType() { return EventType::WindowClose;};

    private:
    };
}
#endif