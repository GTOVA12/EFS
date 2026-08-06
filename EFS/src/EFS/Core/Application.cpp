#include "pch.h"
#include "Application.h"
#include "log.h"
#include "EFS\Events\EventDispatcher.h"
namespace EFS
{

    Application::Application()
    {
        Application::m_Window=Window::Create(Window::WindowData({640,480,"EFS",true,NULL}));
        Application::m_Window->SetEventCallback([this](Event& e) {OnEvent(e); });
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (true)
        {
            Application::m_Window->OnUpdate();
        }
    }
    void Application::OnEvent(Event& event)
    {
        //if (event.GetEventType() == EventType::MouseButtonPressed) 
        //{
        //    OnMouseButtonPressed(static_cast<MouseButtonPressedEvent&>(event));
        //}
        EventDispatcher dispatcher(event);

        if(dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) {return Application::OnKeyPress(event); })) return ;

    }
    bool Application::OnKeyPress(KeyPressedEvent& event)
    {
        EFS_Core_INFO("it workssss");
        return true;
    }


}