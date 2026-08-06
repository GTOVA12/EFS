#include "pch.h"
#include "WindowWindows.h"
namespace EFS
{
	WindowWindows::WindowWindows(const Window::WindowData& props)
	{
		Init(props);
	}
	WindowWindows::~WindowWindows()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}
	void WindowWindows::Init(const Window::WindowData& Data)
	{
		m_Data.Height = Data.Height;
		m_Data.Width = Data.Width;
		m_Data.Title = Data.Title;
		if (glfwInit())
		{
			m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title, NULL, NULL);
			if (!m_Window) { return EFS_Core_ERROR("Probleme d'initialisation de la fenetre"); }
			glfwSetWindowUserPointer(m_Window, &m_Data);
			SetKeyCallback();
		}
	}

	void WindowWindows::SetEventCallback(const std::function<void(Event&)>& func)
	{
		m_Data.EventCallback = func;
	}

	void WindowWindows::OnUpdate()
	{
		glfwPollEvents();        // traite les events en attente (déclenche tes callbacks)
		glfwSwapBuffers(m_Window); // échange les buffers pour afficher le rendu (à ajouter plus tard si tu as un contexte OpenGL)
	}

	void WindowWindows::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0); // 1 = wait until screen refresh(through a signal), 0 = no limit 
		m_Data.VSync = true;
	}

	std::unique_ptr<Window> Window::Create(const WindowData& props)
	{
		return std::make_unique<WindowWindows>(props);
	}

	void WindowWindows::SetKeyCallback()
	{
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData* Data = static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					if (Data->EventCallback) Data->EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					if (Data->EventCallback) Data->EventCallback(event);
					break;
				}
				break;
				}
			});
	}
}