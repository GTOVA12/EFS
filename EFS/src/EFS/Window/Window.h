#pragma once
#include "EFS\Events\Event.h"

namespace EFS {

    class Window
    {
    public:
        struct WindowProps {
            unsigned int Width;
            unsigned int Height;
            const char* Title;
            WindowProps() :Width(640), Height(480), Title("EFS") {};
        };
        virtual ~Window() {}
        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;
        virtual void* GetNativeWindow() const = 0;
        static Window* Create(const WindowProps& props = WindowProps());
    };
}

