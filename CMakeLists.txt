cmake_minimum_required(VERSION 3.16)
project(SnakeGame)

set(CMAKE_CXX_STANDARD 20)

# На Arch с SFML 3 убираем указание версии
find_package(SFML REQUIRED COMPONENTS Graphics Window System)

set(SOURCES
    main.cpp
    lib/Apple.cpp
    lib/Snake.cpp
)

add_executable(SnakeGame ${SOURCES})

# Пути к нашим заголовочным файлам
target_include_directories(SnakeGame PRIVATE lib)

# Линкуем компоненты SFML
target_link_libraries(SnakeGame PRIVATE sfml-graphics sfml-window sfml-system)
