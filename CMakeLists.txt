cmake_minimum_required(VERSION 2.6)
project(qepgviewer)

find_package(Qt5Widgets REQUIRED) 

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(qepgviewer main.cpp ProgrammeView.cpp)

target_link_libraries(qepgviewer Qt5::Widgets)

install(TARGETS qepgviewer RUNTIME DESTINATION bin)
