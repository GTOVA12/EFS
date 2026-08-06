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
project "EFS"
	location "EFS"
	kind "SharedLib"
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
		"EFS/Dependencies/glfw/include"
	}
	links
	{
		"GLFW"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		defines
		{
			"BUILD_API"
		}
		buildoptions
		{
			"/utf-8"
		}

	postbuildcommands
	{
		("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
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
		"EFS/Dependencies/spdlog/include"
	}
	links
	{
		"EFS"
	}
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
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