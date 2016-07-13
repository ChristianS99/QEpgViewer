cmake_minimum_required(VERSION 2.8.11)
project(qepgviewer)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(qepgviewer main.cpp EpgView.cpp Channel.cpp ChannelView.cpp ProgrammeView.cpp)

target_link_libraries(qepgviewer Qt5::Widgets Qt5::Xml)
target_compile_features( qepgviewer PRIVATE cxx_deleted_functions cxx_rvalue_references cxx_range_for )

install(TARGETS qepgviewer RUNTIME DESTINATION bin)
