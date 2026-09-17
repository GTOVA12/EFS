#pragma once
#include "EFS/Core/Layer.h"
#include "EFS/Events/KeyEvent.h"
#include "Shader.h"
namespace EFS {
	enum class Motion
	{
		Stopped,
		Extending,
		Retracting
	};

	class GameLayer : public Layer
	{
	private:
		Shader m_Shader;
		unsigned int VAO, VBO;
		float m_PositionX = -0.5f;
		float m_Speed = 0.25f;
		Motion m_Motion = Motion::Stopped;
		float vertices[18] = {

			 0.5f,-0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
			 -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
		};
		float m_DeltaTime = 0.0f;

	public:
		GameLayer(string VertexFile, string fragmentFile) :m_Shader(Shader(VertexFile, fragmentFile)), VAO(0),VBO(0) {}
		void OnAttach() override ;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		void OnUpdate(float) override;
		bool OnKeyPress(KeyPressedEvent& event);
		void OnImGuiRender() override;
	};
}

