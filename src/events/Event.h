#ifndef DENGINE_EVENT_H
#define DENGINE_EVENT_H

#include <iostream>
#include <string>
#include <functional>

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
    virtual std::string getName() const = 0; ///?

    private:
    };



    class EventDispatcher
    {
    public:
        EventDispatcher(Event& event)
                : event(event)
        {
        }
        template<typename T, typename F>
        bool dispatch(const F& function)
        {
            if (event.getEventType() == T::getStaticType())
            {
                event.handled |= function(static_cast<T&>(event));
                return true;
            }
            return false;
        }
    private:
        Event& event;
    };
};
#endif
