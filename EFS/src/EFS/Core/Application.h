#pragma once
#include "Core.h"
#include "EFS/Window/Window.h"
#include "EFS/Events/KeyEvent.h"
namespace EFS 
{
	class EFSAPI Application
	{
	private:
		std::unique_ptr<Window> m_Window;
	public:
		Application();
		virtual ~Application();
		void Run();
		void OnEvent(Event& event);
		bool OnKeyPress(KeyPressedEvent& event);
	};

	Application* CreateApplication();
}

