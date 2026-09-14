#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "EFS/Core/Core.h"
#include "EFS/Window/Window.h"
#include "EFS/Events/KeyEvent.h"
#include "EFS/Events/ApplicationEvent.h"
#include "EFS/Events/MouseEvent.h"
namespace EFS {

	class EFSAPI WindowWindows : public Window
	{
	
	private:
		struct WindowData {
			unsigned int Width;
			unsigned int Height;
			const char* Title;
			bool VSync;
			std::function<void(Event&)> EventCallback;
		};
		GLFWwindow* m_Window;
		WindowData m_Data;


	public:
		WindowWindows(const WindowProps& props);
		~WindowWindows();
		void Init(const WindowProps& props);
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const std::function<void(Event&)>& func) override;
		void OnUpdate() override;
		void SetVSync(bool enabled) override;
		inline void* GetNativeWindow() const override { return m_Window; }
		inline bool IsVSync() const override { return m_Data.VSync; }
	private:
		void SetKeyCallback();
		void SetWindowCallback();
		void SetMouseCallBack();
	};
}

