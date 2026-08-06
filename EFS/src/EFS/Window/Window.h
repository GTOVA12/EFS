#pragma once
#include "EFS\Events\Event.h"

namespace EFS {

    class Window
    {
    public:
        struct WindowData {
            int Width = 640;
            int Height = 480;
            const char* Title = "EFS";
            bool VSync;
            std::function<void(Event&)> EventCallback;
        };
        virtual ~Window() {}
        virtual void OnUpdate() = 0;
        virtual unsigned int GetWidth() const = 0;
        virtual unsigned int GetHeight() const = 0;
        virtual void SetEventCallback(const std::function<void(Event&)>& callback) = 0;
        virtual void SetVSync(bool enabled) = 0;
        virtual bool IsVSync() const = 0;

        static std::unique_ptr<Window> Create(const WindowData& props);
    };
}

