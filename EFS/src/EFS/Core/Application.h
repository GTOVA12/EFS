#pragma once
#include "Core.h"
#include "EFS/Events/KeyEvent.h"
#include "EFS/Events/ApplicationEvent.h"
#include "LayerStack.h"
namespace EFS 
{
	class Window;
	class ImGuiLayer;

	class EFSAPI Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGui;
		LayerStack m_LayerStack;
		bool m_Running = true;
		static Application* s_Instance;
	public:
		Application();
		virtual ~Application();
		static Application& Get();
		void* GetWindow() const;
		void Run();
		void OnEvent(Event& event);
		bool OnKeyPress(KeyPressedEvent& event);
		bool OnWindowClose(WindowCloseEvent& event);
		void PushLayer(std::unique_ptr<Layer> layer);
		void PushOverlay(std::unique_ptr<Layer> layer);
		void PopLayer(const Layer* layer);
		void PopOverlay(const Layer* layer);
	};

	Application* CreateApplication();
}

