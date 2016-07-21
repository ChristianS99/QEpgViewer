cmake_minimum_required(VERSION 2.8.11)
project(qepgviewer)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Network REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

add_executable(qepgviewer main.cpp EpgView.cpp Channel.cpp ProgrammeView.cpp)
target_link_libraries(qepgviewer Qt5::Widgets Qt5::Xml Qt5::Network)
target_compile_features( qepgviewer PRIVATE cxx_deleted_functions cxx_rvalue_references cxx_range_for )

add_executable(qtableviewtest qtableviewtest.cpp)
target_link_libraries(qtableviewtest Qt5::Widgets)

add_executable(filedownloadertest filedownloader.cpp filedownloadertest.cpp)
target_link_libraries(filedownloadertest Qt5::Network Qt5::Widgets)

install(TARGETS qepgviewer RUNTIME DESTINATION bin)
