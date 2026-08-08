#pragma once
#include "Layer.h"
namespace EFS {
	class EFSAPI LayerStack
	{
	private:
		std::vector<std::unique_ptr<Layer>> m_StackLayers;
		unsigned int m_LayerInsertIndex = 0;
	public:
		void PushLayer(std::unique_ptr<Layer> layer);
		void PushOverlay(std::unique_ptr<Layer> layer);
		void OnUpdate();
		void OnEvent(Event& event);
	};
}
