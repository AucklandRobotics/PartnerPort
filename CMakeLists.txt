cmake_minimum_required(VERSION 2.8)

project(PartnerPort)

set(CMAKE_CXX_FLAGS "-std=c++0x")

include_directories(${PartnerPort_SOURCE_DIR})
link_directories(${PartnerPort_SOURCE_DIR})
include_directories(${PartnerPort_SOURCE_DIR})

add_executable(serial serial.cpp VexJoystick.cpp PartnerPort.cpp)

