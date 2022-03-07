cmake_minimum_required(VERSION 3.16)
project(h264bitstream)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(m4)
include_directories(samples)

add_executable(h264bitstream
        m4/ax_check_debug.m4
        m4/ax_create_pkgconfig_info.m4
        m4/ax_func_getopt_long.m4
        samples/HOWTO.md
        samples/JM_cqm_cabac.264
        samples/JM_cqm_cabac.out
        samples/riverbed-II-360p-48961.264
        samples/riverbed-II-360p-48961.out
        samples/x264_test.264
        samples/x264_test.out
        bs.h
        CHANGES
        circle.yml
        configure.ac
        Doxyfile
        h264_analyze.c
        h264_avcc.c
        h264_avcc.h
        h264_nal.c
        h264_sei.c
        h264_sei.h
        h264_sei.in.c
        h264_slice_data.c
        h264_slice_data.h
        h264_slice_data.in.c
        h264_stream.c
        h264_stream.h
        h264_stream.in.c
        LICENSE
        macroize.pl
        Makefile.am
        Makefile.unix
        MANIFEST
        process.pl
        README.md
        svc_split.c
        TODO)
