#pragma once
#include "Core.h"
#include "EFS/Events/KeyEvent.h"
#include "EFS/Events/ApplicationEvent.h"
#include "LayerStack.h"
namespace EFS 
{
	class Window;
	class LayerStack;

	class EFSAPI Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	public:
		Application();
		~Application();
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

