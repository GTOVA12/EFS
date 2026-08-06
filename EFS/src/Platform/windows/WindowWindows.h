#pragma once
#include "GLFW/glfw3.h"
#include "EFS/Core/Core.h"
#include "EFS/Window/Window.h"
#include "EFS/Events/KeyEvent.h"
namespace EFS {

	class EFSAPI WindowWindows : public Window
	{
	private:
		GLFWwindow* m_Window;
		WindowData m_Data;


	public:
		WindowWindows(const WindowData& props);
		~WindowWindows();
		void Init(const WindowData& props);
		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		void SetEventCallback(const std::function<void(Event&)>& func) override;
		void OnUpdate() override;
		void SetVSync(bool enabled) override;
		virtual bool IsVSync() const override { return m_Data.VSync; }
	private:
		void SetKeyCallback();
	};
}

