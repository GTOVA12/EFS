#pragma once
#include "Core.h"
#include "EFS/Window/Window.h"
#include "EFS/Events/KeyEvent.h"
#include "EFS/Events/ApplicationEvent.h"
#include "LayerStack.h"
namespace EFS 
{
	class EFSAPI Application
	{
	private:
		std::unique_ptr<Window> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& event);
		bool OnKeyPress(KeyPressedEvent& event);
		bool OnWindowClose(WindowCloseEvent& event);
	};

	Application* CreateApplication();
}

