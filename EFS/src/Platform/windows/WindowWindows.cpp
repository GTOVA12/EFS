#include "pch.h"
#include "WindowWindows.h"
namespace EFS
{
	static bool s_IsGLFWInitialized = false;
	static void GLFWErrorCallback(int error, const char* description)
	{
		EFS_Core_ERROR("GLFW Error ({0}): {1}", error, description);
	}
	WindowWindows::WindowWindows(const Window::WindowProps& props)
	{
		Init(props);
	}
	WindowWindows::~WindowWindows()
	{
		EFS_Core_INFO("Destruction of Window Object");
		glfwDestroyWindow(m_Window);
		/*glfwTerminate();*/
	}
	void WindowWindows::Init(const Window::WindowProps& Data)
	{
		m_Data.Height = Data.Height;
		m_Data.Width = Data.Width;
		m_Data.Title = Data.Title;
		EFS_Core_INFO("CreatiNG WINDOW {0} ({1},{2})", m_Data.Title, m_Data.Height, m_Data.Width);
		if (!s_IsGLFWInitialized)
		{
			int success = glfwInit();
			EFS_CORE_ASSERTS(success, "glfw Initialization failed");
			glfwSetErrorCallback(GLFWErrorCallback); /* To display Error related to glfw */
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
			s_IsGLFWInitialized = true;
		}
		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title, NULL, NULL);
		EFS_CORE_ASSERTS(m_Window,"Window Itialization failed");
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		EFS_CORE_ASSERTS(status, "Failed to initialize Glad!");
		SetVSync(true);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetKeyCallback();
		SetWindowCallback();
		SetMouseCallBack();
	}

	void WindowWindows::SetEventCallback(const std::function<void(Event&)>& func)
	{
		m_Data.EventCallback = func;
	}

	void WindowWindows::OnUpdate()
	{
		glfwPollEvents();        // traite les events en attente (déclenche les callbacks)
		glfwSwapBuffers(m_Window); // échange les buffers pour afficher le rendu (pour OPENGL)
	}

	void WindowWindows::SetVSync(bool enabled)
	{
		glfwSwapInterval(enabled ? 1 : 0); // 1 = wait until screen refresh(through a signal), 0 = no limit 
		m_Data.VSync = enabled;
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowWindows(props);
	}

	/*Relative to callback function on Event */
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
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						if (Data->EventCallback) Data->EventCallback(event);
						break;
					}
				
				}
			});
	}

	void WindowWindows::SetWindowCallback()
	{
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				WindowCloseEvent event{};
				if (data.EventCallback) data.EventCallback(event);

			});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& Data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));
				Data.Width = width;
				Data.Height = height;

				WindowResizeEvent event(width, height);
				Data.EventCallback(event);
			});

	}
	void WindowWindows::SetMouseCallBack()
	{
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(static_cast<WindowData*>(glfwGetWindowUserPointer(window)));

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}
}