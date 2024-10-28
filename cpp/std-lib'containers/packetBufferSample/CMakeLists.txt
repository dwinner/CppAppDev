cmake_minimum_required(VERSION 3.29)
project(packetBufferSample)

set(CMAKE_CXX_STANDARD 23)

add_executable(packetBufferSample main.cpp
        PacketBuffer.hpp
        IPPacket.hpp)
