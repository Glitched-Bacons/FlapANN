workspace "FlapANN"
    architecture "x64"

    configurations
    {
        "Debug",
        "Release"
    }

    filter "configurations:Debug"
        defines "_DEBUG"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines "_RELEASE"
        runtime "Release"
        optimize "On"
        
    
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "FlapANN"
    location "FlapANN"
    kind "ConsoleApp"
    language "C++"

    targetdir("bin/" .. outputdir .. "/%{wks.name}")
    objdir("bin-int/" .. outputdir .. "/%{wks.name}")

    pchheader "pch.h"
    pchsource "%{wks.name}/src/pch.cpp"

    files
    {
        -- main source files
        "%{wks.name}/src/**.h",
        "%{wks.name}/src/**.cpp",

        -- vendors
        "%{wks.name}/vendor/src/**.cpp",
        "%{wks.name}/vendor/src/**.c"
    }

    includedirs
    {
        "%{wks.name}/vendor/include",
        "%{wks.name}/src"
    }

    filter "system:windows"
        cppdialect "C++17"
        systemversion "latest"

        defines
        {
            "SFML_STATIC",
        }

        libdirs
        {
            "%{wks.name}/vendor/lib/imgui/windows",
            "%{wks.name}/vendor/lib/imgui-sfml/windows",
            "%{wks.name}/vendor/lib/SFML/windows",
            "%{wks.name}/vendor/lib/fann/windows"
        }

        links
        {
            -- SFML
            "opengl32",
            "freetype",
            "winmm",
            "gdi32",
            "openal32",
            "flac",
            "vorbisenc",
            "vorbisfile",
            "vorbis",
            "ogg",

            -- FANN
            "fann"
        }

        postbuildcommands
        {
            ('{COPYFILE} ../%{wks.name}/vendor/lib/SFML/windows/openal32.dll %{cfg.buildtarget.bundlepath}'),
            ('{COPYFILE} ../%{wks.name}/vendor/lib/fann/windows/fann.dll %{cfg.buildtarget.bundlepath}'),
            ('{COPYDIR} ../%{wks.name}/resources %{cfg.buildtarget.bundlepath}/resources')
        }

        filter {"configurations:Debug", "system:windows"}
            links { "sfml-audio-s-d", "sfml-graphics-s-d", "sfml-network-s-d", "sfml-system-s-d", "sfml-window-s-d" }

        filter {"configurations:Release", "system:windows"}
            links { "sfml-audio-s", "sfml-graphics-s", "sfml-network-s", "sfml-system-s", "sfml-window-s" }
        
        filter "files:**.c"
            flags {"NoPCH"}

        filter "files:FlapANN/vendor/src/**.cpp"
            flags {"NoPCH"}

