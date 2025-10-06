cmake_minimum_required(VERSION 3.16.3)

project(lecture3_homework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
message(STATUS "--------------------CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}--------------------")
find_package(PkgConfig REQUIRED)  
pkg_check_modules(LIBUSB REQUIRED libusb-1.0)  
include_directories(${LIBUSB_INCLUDE_DIRS})
find_package(OpenCV REQUIRED)
find_package(fmt REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(yaml-cpp REQUIRED)
set(OpenVINO_DIR "/opt/intel/openvino_2024.6.0/runtime/cmake/")
find_package(OpenVINO REQUIRED)

include_directories(${EIGEN3_INCLUDE_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

add_subdirectory(io)
add_subdirectory(tasks)
add_subdirectory(tools)

add_executable(main main.cpp)


target_link_libraries(main ${OpenCV_LIBS} ${LIBUSB_LIBRARIES} fmt::fmt yaml-cpp tools io auto_aim)

