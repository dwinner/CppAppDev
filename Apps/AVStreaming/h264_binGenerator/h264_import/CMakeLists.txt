cmake_minimum_required(VERSION 3.16)
project(h264_import)

set(CMAKE_CXX_STANDARD 17)

add_executable(h264_import main.cpp Nalu.h H264FileReader.h H264FileReader.cpp importGeneratorUtils.cpp importGeneratorUtils.h)