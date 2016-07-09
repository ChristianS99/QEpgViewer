cmake_minimum_required(VERSION 2.6)
project(qepgviewer)

add_executable(qepgviewer main.cpp)

install(TARGETS qepgviewer RUNTIME DESTINATION bin)
