#include "pch.h"
#include "ImGuiLayer.h"
#include "EFS/Core/Application.h"
#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>
namespace EFS {
	ImGuiLayer::ImGuiLayer():Layer("Debug")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui::StyleColorsDark();

		GLFWwindow* window = (GLFWwindow*)(Application::Get().GetWindow());
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 460");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplGlfw_Shutdown();
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}


	void ImGuiLayer::OnEvent(Event& event)
	{
		const ImGuiIO& io = ImGui::GetIO();
		if (event.IsInCategorie(EFS::EventCategoryMouse) && io.WantCaptureMouse)
		{
			event.MarkHandled();
		}
		if (event.IsInCategorie(EFS::EventCategoryKeyboard) && io.WantCaptureKeyboard)
		{
			event.MarkHandled();
		}
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnImGuiRender()
	{
		//static int compteur = 0;
		//if (ImGui::Begin("Mon premier Panneau"))
		//{
		//	ImGui::Text("Compteur : %d", compteur);
		//	if (ImGui::Button("Incrementer"))
		//		compteur++;
		//}
		//ImGui::End();
	}

}
