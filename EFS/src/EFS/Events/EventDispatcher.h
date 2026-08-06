#pragma once
#include "Event.h"
namespace EFS {

    class EFSAPI EventDispatcher
    {
    private:
        Event& m_event;
    public:
        EventDispatcher(Event& e) :m_event(e) {};
        template<typename T>
        bool Dispatch(const std::function<bool(T&)>& func)
        {
            if (m_event.GetEventType() == T::GetStaticType())
            {
                m_event.m_Handled=func(static_cast<T&>(m_event));
                return true;
            }
            return false;
        }
    };
}