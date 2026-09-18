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
		unsigned int VAO, VBO, CBO, EBO;
		float m_PositionX = -0.5f;
		float m_Speed = 0.25f;
		Motion m_Motion = Motion::Stopped;
		float vertices[12] = {
			 0.5f,  0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		unsigned int indices[6] = { 0, 1, 3, 1, 2, 3 };
		float colors[12] = {
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 0.0f
		};
		float m_DeltaTime = 0.0f;

	public:
		GameLayer(string VertexFile, string fragmentFile) :m_Shader(Shader(VertexFile, fragmentFile)), VAO(0),VBO(0),CBO(0),EBO(0) {}
		void OnAttach() override ;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		void OnUpdate(float) override;
		bool OnKeyPress(KeyPressedEvent& event);
		void OnImGuiRender() override;
	};
}

