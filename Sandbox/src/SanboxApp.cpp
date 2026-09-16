#include "EFS.h"
#include "GameLayer.h"

class Sandbox : public EFS::Application
{
public:
	Sandbox()
	{
		PushLayer(std::make_unique<EFS::GameLayer>("C:\\Dev\\DevC++\\EFS\\Sandbox\\Shader\\VertexShader.glsl","C:\\Dev\\DevC++\\EFS\\Sandbox\\Shader\\FragmentShader.glsl"));
	}
	~Sandbox()
	{

	}

};
EFS::Application* EFS::CreateApplication()
{
	return new Sandbox;
}