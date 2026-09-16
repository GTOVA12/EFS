#pragma once
#include "EFS/Core/Layer.h"
#include "EFS/Events/KeyEvent.h"
#include "Shader.h"
namespace EFS {

	class GameLayer : public Layer
	{
	private:
		Shader m_Shader;
		unsigned int VAO, VBO;
		float vertices[18] = {

			 0.5f,-0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
			 -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
			 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
		};

	public:
		GameLayer(string VertexFile, string fragmentFile) :m_Shader(Shader(VertexFile, fragmentFile)), VAO(0),VBO(0) {}
		void OnAttach() override ;
		void OnDetach() override;
		void OnEvent(Event& event) override;
		void OnUpdate() override;
		bool OnKeyPress(KeyPressedEvent& event);
		void OnImGuiRender() override;
	};
}

