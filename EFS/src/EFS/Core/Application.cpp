#include "pch.h"
#include "Application.h"
#include "EFS\Events\EventDispatcher.h"
#include "GameLayer.h"
namespace EFS
{
#define BND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)

    Application::Application()
    {
        Application::m_Window=std::unique_ptr<Window>(Window::Create());
        Application::m_Window->SetEventCallback([this](Event& e) {OnEvent(e); });
        Application::m_LayerStack.PushLayer(std::unique_ptr<Layer>(new GameLayer()));
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            Application::m_Window->OnUpdate();
            Application::m_LayerStack.OnUpdate();
        }
    }
    void Application::OnEvent(Event& event)
    {
        Application::m_LayerStack.OnEvent(event);
        //if (event.GetEventType() == EventType::MouseButtonPressed) 
        //{
        //    OnMouseButtonPressed(static_cast<MouseButtonPressedEvent&>(event));
        //}
        EFS_Core_INFO("Event {0}", event);
        EventDispatcher dispatcher(event);

        if(dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) {return Application::OnKeyPress(event); })) return ;
       /* if(dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) {return Application::OnWindowClose(event); })) return;*/
        if (dispatcher.Dispatch < WindowCloseEvent>(BND_EVENT_FN(OnWindowClose))) return;

    }
    bool Application::OnKeyPress(KeyPressedEvent& event)
    {
        EFS_Core_INFO("it workssss");
        return true;
    }
    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        EFS_Core_INFO("Close event {0}",event.ToString());
        m_Running = false;
        //m_Window->~Window();
        return true;
    }


}