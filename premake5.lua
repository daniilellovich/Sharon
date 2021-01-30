workspace "Sharon"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}


outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "Sharon/vendor/GLFW/include"
IncludeDir["Glad"] = "Sharon/vendor/Glad/include"
IncludeDir["ImGui"] = "Sharon/vendor/imgui"
IncludeDir["glm"] = "Sharon/vendor/glm"

group "Dependencies"
	include "Sharon/vendor/GLFW"
	include "Sharon/vendor/Glad"
	include "Sharon/vendor/imgui"

group ""

project "Sharon"
	location "Sharon"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "sharon_pch.h"
	pchsource "Sharon/src/sharon_pch.cpp" --only for VisualStudio

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"Sharon/src", 
		"%{prj.name}/vendor/spdlog/include",	
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib",
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SHARON_PLATFORM_WINDOWS",
			"SHARON_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		--postbuildcommands
		--{
		--	("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputDir .. "/Sandbox/\"")
		--}

	filter "configurations:Debug"
		defines "SHARON_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SHARON_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SHARON_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

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
		"Sharon/vendor",
		"%{IncludeDir.glm}"
	}

	links
	{
		"Sharon"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"SHARON_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "SHARON_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SHARON_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SHARON_DIST"
		runtime "Release"
		optimize "on"