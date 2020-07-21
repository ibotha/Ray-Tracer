workspace "Ray-Tracer"

startproject "Ray-Tracer"
architecture "x64"

configurations
{
	"Debug",
	"Release",
	"Dist"
}
dir = "Ray-Tracer/"
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

IncludeDir = {}
IncludeDir["olcPixelGameEngine"] = "vendor/olcPixelGameEngine"
IncludeDir["glm"] = "vendor/glm"

group "Dependencies"
project "olcPixelGameEngine"
	localdir = "Ray-Tracer/vendor/olcPixelGameEngine/"
    kind "StaticLib"
    language "C"
    
	targetdir (localdir .. "bin/" .. outputdir .. "/%{prj.name}")
    objdir (localdir .. "bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		localdir .. "olcExampleProgram.cpp"
    }
    filter { "system:windows", "configurations:Release" }
        buildoptions "/MT"
group ""

project "Ray-Tracer"
	location "Ray-Tracer"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/%{IncludeDir.olcPixelGameEngine}",
		"%{prj.name}/%{IncludeDir.glm}"
	}

	links
	{
		"olcPixelGameEngine"
	}
	
	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "SW_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "SW_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "SW_DIST"
		runtime "Release"
		optimize "on"
