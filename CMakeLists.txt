cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(app
src/main.cpp
src/launch_pad.cpp
src/game.cpp
src/window.cpp
src/particle.cpp
src/random.cpp
src/ui_background.cpp
src/ui_manager.cpp
src/ui_button.cpp
src/utils.cpp
src/ui_dial.cpp
src/ui_slider.cpp
src/level.cpp
src/ui_text.cpp
src/level_1.cpp
src/ui_element.cpp
src/ui_collider.cpp
src/level_2.cpp
src/sound_player.cpp
src/level_0.cpp
)

target_compile_features(app PRIVATE cxx_std_17)
target_link_libraries(app PRIVATE SFML::Graphics SFML::Audio)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT app)

add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:app>/assets
)

if(MINGW)
    target_link_options(app PRIVATE
        -static-libgcc
        -static-libstdc++
    )
endif()