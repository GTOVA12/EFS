#pragma once
#include "EFS/Core/Layer.h"
#include "EFS/Events/KeyEvent.h"
namespace EFS {

	class GameLayer : public Layer
	{
	public:
		GameLayer() = default;
		void OnEvent(Event& event) override;
		bool GameLayer::OnKeyPress(KeyPressedEvent& event);
	};
}

