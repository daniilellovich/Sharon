workspace "Sharon"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputDir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Sharon"
	location "Sharon"
	kind "SharedLib"
	language "C++"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	pchheader "sharon_pch.h"
	pchsource "Sharon/src/sharon_pch.cpp" --only for VisualStudio

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",	
		"Sharon/src"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SHARON_PLATFORM_WINDOWS",
			"SHARON_BUILD_DLL"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputDir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "SHARON_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SHARON_Release"
		symbols "On"

	filter "configurations:Dist"
		defines "SHARON_DIST"
		symbols "On"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	targetdir("bin/" .. outputDir .. "/%{prj.name}")
	objdir("bin-int/" .. outputDir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Sharon/vendor/spdlog/include",
		"Sharon/src"
	}

	links
	{
		"Sharon"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"SHARON_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "SHARON_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "SHARON_RELEASE"
		symbols "On"

	filter "configurations:Dist"
		defines "SHARON_DIST"
		symbols "On"

	filter {"system:windows", "configurations:Release"}
		buildoptions "/MT"