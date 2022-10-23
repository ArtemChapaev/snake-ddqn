cmake_minimum_required(VERSION 3.16)
project(snake)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(cpp-terminal)

include_directories(include)

add_executable(snake /
        src/snake.cpp /
        src/mapModel.cpp /
        src/control.cpp /
        src/keyboardControl.cpp /
        src/mapView.cpp /
        src/consoleUI.cpp /
        src/game.cpp /
        src/main.cpp /
        src/graphics.cpp /
        src/settings.cpp /
        src/logos.cpp /
        src/menu.cpp /
        )

target_link_libraries(snake PRIVATE cpp-terminal)
