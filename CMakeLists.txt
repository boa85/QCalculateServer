cmake_minimum_required(VERSION 3.7)
project(QCalculateServer)


set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-O0 -pedantic-errors -Wextra -Wall -Winit-self -Wold-style-cast -Woverloaded-virtual -Wuninitialized -Wmissing-declarations -Wno-ignored-qualifiers -Wno-unused-parameter")
find_package(Boost 1.58.0 COMPONENTS regex serialization program_options signals)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Could not find boost!")
endif ()
include_directories(${BOOST_INCLUDE_DIRS})
set(CMAKE_PREFIX_PATH "/opt/soft/qt/5.8/gcc_64/")#указать путь к  Qt
set(CMAKE_AUTOMOC ON)#Q_OBJECT - для использования в проекте механизма сигналов и слотов.
find_package(Qt5Core REQUIRED)# по аналогии с *.pro QT += gui core
find_package(Qt5Network REQUIRED)#Сеть

set(SOURCE_FILES main.cpp CLI/src/ArgumentParser.cpp CLI/include/ArgumentParser.hpp config/src/config.cpp config/include/config.hpp)
add_executable(QCalculateServer ${SOURCE_FILES})
target_link_libraries(QCalculateServer Qt5::Core Qt5::Network
        ${Boost_LIBRARIES})# с которыми будем линковать бинарник