#include "pch.h"
#include "LayerStack.h"

namespace EFS {
	void LayerStack::PushLayer(std::unique_ptr<Layer> layer)
	{
		layer->OnAttach();
		m_StackLayers.emplace(m_StackLayers.begin() + m_LayerInsertIndex,std::move(layer));
		m_LayerInsertIndex++;
	}
	void LayerStack::PushOverlay(std::unique_ptr<Layer> layer)
	{
		layer->OnAttach();
		m_StackLayers.emplace_back(std::move(layer));
	}
	void LayerStack::OnUpdate()
	{
		for (std::unique_ptr<Layer>& layer : m_StackLayers)
		{
			layer->OnUpdate();
		}
	}
	void LayerStack::OnEvent(Event& event)
	{
		for (auto it = m_StackLayers.rbegin(); it != m_StackLayers.rend(); it++)
		{
			(*it)->OnEvent(event);
			if (event.m_Handled)
				break;
		}
	}
}