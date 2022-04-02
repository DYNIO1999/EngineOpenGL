#ifndef DENGINE_EVENT_H
#define DENGINE_EVENT_H

#include <iostream>
#include <string>

namespace  DEngine {

    enum class EventType{
        None = 0,
        WindowClose,
        WindowResize,
        KeyPressed,
        KeyReleased,
        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };


    class Event {

    public:

    virtual ~Event() = default;
    bool handled = false;
    virtual EventType getEventType() const = 0;
    virtual const char* getName() const = 0; ///?
    virtual std::string toString() const { return getName(); }

    private:
    };
};
#endif
