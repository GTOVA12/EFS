workspace "EFS"
	architecture "x64"
	startproject "Sandbox"
	configurations 
   { 
	"Debug",
	"Release",
	"Dist" 
   }

   outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "EFS/Dependencies/glfw" 
include "EFS/Dependencies/glad"
include "EFS/Dependencies/ImGui"

project "EFS"
	location "EFS"
	kind "StaticLib"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	pchheader "pch.h"
	pchsource "EFS/src/pch.cpp"

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/Dependencies/spdlog/include",
		"%{prj.name}/Dependencies/glfw/include",
		"%{prj.name}/Dependencies/glad/include",
		"%{prj.name}/Dependencies/ImGui",
		"%{prj.name}/Dependencies/glm"
		
	}
	links
	{
		"GLFW","glad","ImGui"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"BUILD_API",
			"EFS_STATIC"
		}
		buildoptions
		{
			"/utf-8"
		}

	disablewarnings { "4251" }
	
	filter "configurations:Debug"
		defines {"EFS_DEBUG","EFS_ENABLE_ASSERTS"}
		symbols "On"

	filter "configurations:Release"
		defines "EFS_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "EFS_DIST"
		symbols "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/"..outputdir.."/%{prj.name}")
	objdir ("bin-int/"..outputdir.."/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/src/**.h"
	}
	includedirs
	{
		"EFS/src",
		"EFS/Dependencies/spdlog/include",
		"EFS/Dependencies/ImGui",
		"EFS/Dependencies/glm",
		"EFS/Dependencies/glad/include"

	}
	links
	{
		    "EFS",
			"ImGui",
			"GLFW",
			"glad",
			"opengl32.lib"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"EFS_STATIC"
		}
		buildoptions
		{
			"/utf-8"
		}

	filter "configurations:Debug"
		defines "EFS_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "EFS_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "EFS_DIST"
		symbols "On"