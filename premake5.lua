workspace "Sharon"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

	startproject "Sandbox"

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Sharon/vendor/GLFW/include"
IncludeDir["Glad"] = "Sharon/vendor/Glad/include"
IncludeDir["ImGui"] = "Sharon/vendor/imgui"

group "Dependencies"
	include "Sharon/vendor/GLFW"  -- pastes file premake5.lua from GLFW folder
	include "Sharon/vendor/Glad"
	include "Sharon/vendor/imgui"

group ""

project "Sharon"
	location "Sharon"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "sharon_pch.h"
	pchsource "Sharon/src/sharon_pch.cpp" --only for VisualStudio

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"Sharon/src", 
		"%{prj.name}/vendor/spdlog/include",	
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SHARON_PLATFORM_WINDOWS",
			"SHARON_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "SHARON_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SHARON_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "SHARON_DIST"
		runtime "Release"
		symbols "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Sharon/src",
		"Sharon/vendor/spdlog/include",
	}

	links
	{
		"Sharon"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"SHARON_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "SHARON_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "SHARON_RELEASE"
		runtime "Release"
		symbols "On"

	filter "configurations:Dist"
		defines "SHARON_DIST"
		runtime "Release"
		symbols "On"