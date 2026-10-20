
cmake_minimum_required(VERSION 3.21)

project(Catalyst LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_PREFIX_PATH "D:/qt/6.12.0/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(Catalyst
    src/main.cpp

    src/ui/WelcomePage.h
    src/ui/WelcomePage.cpp

    src/ui/AuthWindow.h
    src/ui/AuthWindow.cpp

    src/ui/admin/AdminPortal.h
    src/ui/admin/AdminPortal.cpp

    src/ui/faculty/FacultyPortal.h
    src/ui/faculty/FacultyPortal.cpp
)

target_link_libraries(Catalyst PRIVATE Qt6::Widgets)
