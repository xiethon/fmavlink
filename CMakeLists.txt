cmake_minimum_required(VERSION 3.20)

project(fmavlink LANGUAGES C CXX)

option(FMAVLINK_ENABLE_CPP11 "Generate C++11 MAVLink headers" ON)
option(FMAVLINK_BUILD_EXAMPLES "Build fmavlink examples" OFF)

set(FMAVLINK_GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/generated")
set(FMAVLINK_C_OUT "${FMAVLINK_GENERATED_DIR}/c")
set(FMAVLINK_CPP11_OUT "${FMAVLINK_GENERATED_DIR}/cpp11")

if(NOT EXISTS "${FMAVLINK_C_OUT}/fmavlink/mavlink.h")
    message(FATAL_ERROR
        "Missing generated C headers. Run ./tools/generate.sh before using fmavlink."
    )
endif()

add_library(fmavlink INTERFACE)
add_library(fmavlink::fmavlink ALIAS fmavlink)
target_include_directories(fmavlink
    INTERFACE
        "${FMAVLINK_C_OUT}"
)

if(FMAVLINK_ENABLE_CPP11)
    if(NOT EXISTS "${FMAVLINK_CPP11_OUT}/fmavlink/mavlink.h")
        message(FATAL_ERROR
            "Missing generated C++11 headers. Run ./tools/generate.sh before enabling FMAVLINK_ENABLE_CPP11."
        )
    endif()

    add_library(fmavlink_cpp11 INTERFACE)
    add_library(fmavlink::cpp11 ALIAS fmavlink_cpp11)
    target_include_directories(fmavlink_cpp11
        INTERFACE
            "${FMAVLINK_CPP11_OUT}"
    )
endif()

if(FMAVLINK_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
