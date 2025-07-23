workspace "GameEngine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["GLFW"] = "GameEngine/vendor/GLFW/include"
IncludeDir["glad"] = "GameEngine/vendor/glad/include"
IncludeDir["glm"] = "GameEngine/vendor/glm-master"
IncludeDir["imgui"] = "GameEngine/vendor/imgui-docking"
IncludeDir["stb_image"] = "GameEngine/vendor/stb_image"

include "GameEngine/vendor/GLFW"

project "GameEngine"
	location "GameEngine"
	kind "SharedLib"
	language "C++"
	buildoptions { "/MP" }	

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "gepch.h"
	pchsource ("%{prj.name}/src/gepch.cpp")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/assets/shaders/**.vert",
		"%{prj.name}/assets/shaders/**.frag",
		"%{prj.name}/vendor/glad/src/**.c",
		"%{prj.name}/vendor/imgui-docking/*.cpp",
		"%{prj.name}/vendor/imgui-docking/backends/imgui_impl_glfw.cpp",
		"%{prj.name}/vendor/imgui-docking/backends/imgui_impl_opengl3.cpp",
		"%{prj.name}/vendor/stb_image/*.h",
		"%{prj.name}/vendor/stb_image/*.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb_image}"
	}
	
	links
	{
		"GLFW",
		"opengl32.lib"
	}

	postbuildcommands
	{
		("{MKDIR} ../bin/" .. outputdir .. "/Sandbox/"),
		("{COPYFILE} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox/")
	}

	filter "files:GameEngine/vendor/**.cpp"
		flags { "NoPCH" }

	filter "files:GameEngine/vendor/**.c"
		flags { "NoPCH" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GE_PLATFORM_WINDOWS",
			"GE_BUILD_DLL"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	buildoptions {"/utf-8"}

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	debugdir "../GameEngine/GameEngine"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/src",
		"GameEngine/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.glad}",
		"%{IncludeDir.glm}",
		"%{IncludeDir.imgui}",
		"%{IncludeDir.stb_image}"
	}

	links
	{
		"GameEngine"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"GE_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "GE_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "GE_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "GE_DIST"
		optimize "On"