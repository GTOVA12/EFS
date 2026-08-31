#include "EFS.h"
#include "GameLayer.h"

class Sandbox : public EFS::Application
{
public:
	Sandbox()
	{
		PushOverlay(std::make_unique<EFS::GameLayer>());
	}
	~Sandbox()
	{

	}

};
EFS::Application* EFS::CreateApplication()
{
	return new Sandbox;
}