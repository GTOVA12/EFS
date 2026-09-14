#include "pch.h"
#include "Application.h"
#include "EFS/Window/Window.h"
#include "EFS/Events/EventDispatcher.h"
#include "glad/glad.h"
#include "EFS/ImGui/ImGuiLayer.h"
namespace EFS
{
#define BIND_EVENT_FN(x) std::bind(&Application::x,this,std::placeholders::_1)
    Application* Application::s_Instance = nullptr;
    Application::Application()
    {
        s_Instance = this;
        Application::m_Window=std::unique_ptr<Window>(Window::Create());
        Application::m_Window->SetEventCallback([this](Event& e) {OnEvent(e); });
        auto ImGui = std::make_unique<ImGuiLayer>();
        m_ImGui = ImGui.get();
        m_LayerStack.PushOverlay(std::move(ImGui));
    }

    Application::~Application()
    {
    }

    Application& Application::Get()
    {
        return *s_Instance;
    }

    void* Application::GetWindow() const
    {
       return m_Window->GetNativeWindow();
    }

    void Application::Run()
    {
        EFS_Core_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
        EFS_Core_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
        EFS_Core_INFO("  Version: {0}", (const char*)glGetString(GL_VERSION));
        while (m_Running)
        {
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
            Application::m_LayerStack.OnUpdate();
            Application::m_ImGui->Begin();
            Application::m_LayerStack.OnImGuiRender();
            Application::m_ImGui->End();
            Application::m_Window->OnUpdate();
        }
    }
    void Application::OnEvent(Event& event)
    {
        Application::m_LayerStack.OnEvent(event);
       // EFS_Core_INFO("Event {0}", event);
        EventDispatcher dispatcher(event);

       // if(dispatcher.Dispatch<KeyPressedEvent>([this](KeyPressedEvent& event) {return Application::OnKeyPress(event); })) return ;
       ///* if(dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& event) {return Application::OnWindowClose(event); })) return;*/
       if (dispatcher.Dispatch < WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose))) return;

    }
    void Application::PushLayer(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushLayer(std::move(layer));
    }
    void Application::PushOverlay(std::unique_ptr<Layer> layer)
    {
        m_LayerStack.PushOverlay(std::move(layer));
    }
    void Application::PopLayer(const Layer* layer)
    {
        m_LayerStack.PopLayer(layer);
    }
    void Application::PopOverlay(const Layer* layer)
    {
        m_LayerStack.PopOverlay(layer);
    }
    bool Application::OnWindowClose(WindowCloseEvent& event)
    {
        EFS_Core_INFO("Close event {0}",event.ToString());
        m_Running = false;
        return true;
    }


}