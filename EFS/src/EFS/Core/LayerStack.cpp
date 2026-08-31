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
	void LayerStack::PopLayer(const Layer* layer)
	{
		auto it = std::find_if(m_StackLayers.begin(), m_StackLayers.begin() + m_LayerInsertIndex,
			[layer](const std::unique_ptr<Layer>& l) { return (layer == l.get()); });

		if (it != m_StackLayers.begin() + m_LayerInsertIndex)
		{
			(*it)->OnDetach();
			m_StackLayers.erase(it);
			m_LayerInsertIndex--;
		}
	}
	void LayerStack::PopOverlay(const Layer* layer)
	{
		auto it = std::find_if(m_StackLayers.begin() + m_LayerInsertIndex, m_StackLayers.end(),
			[layer](const std::unique_ptr<Layer>& l) { return (layer == l.get()); });

		if (it != m_StackLayers.end())
		{
			(*it)->OnDetach();
			m_StackLayers.erase(it);
		}
	}
	LayerStack::~LayerStack()
	{
		for (std::unique_ptr<Layer>& layer : m_StackLayers)
		{
			layer->OnDetach();
		}
	}
}