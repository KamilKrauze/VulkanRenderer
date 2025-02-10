workspace "VulkanRenderer"
    architecture "x64"
    configurations { "Debug", "Release", "Shipping" }

project "VulkanRenderer"
    location "src"
    kind "ConsoleApp"
    language "C++"
    
    targetdir "build/%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

    files { 
        "./src/**.h",
        "./src/**.hpp",
        "./src/**.c",
        "./src/**.cpp"
    }

    includedirs {
        -- Project source code
        "./src/",
        
        -- Thirdparty
        "./thirdparty/include/",
        "./thirdparty/include/glm/",
        "./thirdparty/include/glfw/include"
    }

    libdirs {
        "./thirdparty/lib/"
    }

    links {"glfw3", "vulkan-1"}

-- Windows system
    filter "system:windows"
        system "windows"
        cppdialect "C++17"
        systemversion "latest"
-- Linux system
    filter "system:linux"
        system "linux"
        cppdialect "gnu++17"
        buildoptions { "-fopenmp" }
        links { "omp", "glfw", "GL", "m", "X11", "pthread", "Xi", "Xrandr", "dl" }

-- Build configurations
    filter "configurations:Debug"
        defines "DEBUG"
        symbols "On"

    filter "configurations:Release"
        defines "NDEBUG"
        optimize "On"

    filter "configurations:Shipping"
        defines {"SHIPPING"}
        toolset "clang"
        optimize "On"
        flags { "MultiProcessorCompile" }
        debugdir "%{prj.location}/.."
