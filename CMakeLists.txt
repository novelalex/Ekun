cmake_minimum_required(VERSION 3.5)
project(Ekun)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/env")

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2/cmake")
set(SDL2_image_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2_image/cmake")
set(SDL2_mixer_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2_mixer/cmake")
set(SDL2_ttf_DIR "${CMAKE_SOURCE_DIR}/vendor/SDL2_ttf/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

set(GLEW_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/glew/include")
set(GLEW_LIBRARY "${CMAKE_SOURCE_DIR}/vendor/glew/lib/Release/x64/glew32.lib")

set(GLM_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/glm")

set(MRUBY_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/vendor/mruby/include")
set(MRUBY_LIBRARY "${CMAKE_SOURCE_DIR}/vendor/mruby/build/host/lib/libmruby.lib")
set(MRUBY_CORE_LIBRARY "${CMAKE_SOURCE_DIR}/vendor/mruby/build/host/lib/libmruby_core.lib")

set(IMGUI_DIR "${CMAKE_SOURCE_DIR}/vendor/imgui")
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/backends/imgui_impl_sdl2.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl2.cpp
)

include_directories(
        ${SDL2_INCLUDE_DIRS}
        ${GLEW_INCLUDE_DIR}
        ${GLM_INCLUDE_DIR}
        ${MRUBY_INCLUDE_DIR}
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

# add_executable(Ekun ${IMGUI_SOURCES}
add_executable(Ekun ${IMGUI_SOURCES}
        src/Main.cpp
        src/core/GameManager.cpp
        src/core/Debug.cpp
        src/core/Window.cpp
        src/core/Window.h
        src/core/Timer.cpp
        src/core/Timer.h
        src/core/Game.cpp
        src/core/Game.h
        src/scripting/MRuby.cpp
        src/scripting/MRuby.h
        src/graphics/Sprite.cpp
        src/graphics/Sprite.h
        src/scripting/Script.cpp
        src/scripting/Script.h
        src/core/Ekun.h
        src/graphics/Font.cpp
        src/graphics/Font.h
        src/core/InputHandler.cpp
        src/core/InputHandler.h
        src/core/SaveSystem.cpp
        src/core/SaveSystem.h
        src/scripting/MRubyUtils.cpp
        src/scripting/MRubyUtils.h
        src/core/StoryPlayer.cpp
        src/core/StoryPlayer.h "src/graphics/TextBox.h" "src/graphics/TextBox.cpp"
        src/graphics/Button.cpp
        src/graphics/Button.h)

target_link_libraries(Ekun
        ${SDL2_LIBRARIES}
        SDL2_image::SDL2_image
        SDL2_mixer::SDL2_mixer
        SDL2_ttf::SDL2_ttf
        ${GLEW_LIBRARY}
        ${MRUBY_LIBRARY}
        ${MRUBY_CORE_LIBRARY}
        ws2_32
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Ekun)

if(MSVC)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:MSVCRT")
endif()

if (MSVC)
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

    set(CMAKE_CXX_FLAGS_DEBUG "/MDd /Zi /Ob0 /Od /RTC1")
    target_compile_definitions(Ekun PRIVATE "$<$<CONFIG:Debug>:DEBUG>")

    set(CMAKE_CXX_FLAGS_RELEASE "/MD /O2 /Ob2 /DNDEBUG")
    target_compile_definitions(Ekun PRIVATE "$<$<CONFIG:Release>:NDEBUG>")
else ()
    set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "" FORCE)

    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    target_compile_definitions(Ekun PRIVATE "$<$<CONFIG:Debug>:DEBUG>")

    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    target_compile_definitions(Ekun PRIVATE "$<$<CONFIG:Release>:NDEBUG>")
endif ()

find_package(OpenGL REQUIRED)
target_link_libraries(Ekun OpenGL::GL)