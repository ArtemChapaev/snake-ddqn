cmake_minimum_required(VERSION 3.16)
project(snake)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(snake /
        src/snake.cpp /
        src/mapModel.cpp /
        src/control.cpp /
        src/mapView.cpp /
        src/consoleUI.cpp /
        src/game.cpp /
        src/main.cpp /
        )
