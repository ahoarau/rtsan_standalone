cmake_minimum_required(VERSION 3.22)

project(rtsan_standalone VERSION 1.0.0 LANGUAGES CXX)

add_library(rtsan::rtsan_standalone STATIC IMPORTED GLOBAL)
set_target_properties(rtsan::rtsan_standalone PROPERTIES
    INTERFACE_COMPILE_OPTIONS -fsanitize=realtime
    INTERFACE_LINK_OPTIONS -fsanitize=realtime
    INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set_target_properties(rtsan::rtsan_standalone PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/macos/libclang_rt.rtsan_osx_dynamic.dylib
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86_64")
    set_target_properties(rtsan::rtsan_standalone PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/linux/libclang_rt.rtsan_linux_x86_64.a
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux" AND CMAKE_SYSTEM_PROCESSOR STREQUAL "aarch64")
    set_target_properties(rtsan::rtsan_standalone PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/linux/libclang_rt.rtsan_linux_aarch64.a
    )
else()
    message(FATAL_ERROR "
        CMAKE_SYSTEM_NAME:${CMAKE_SYSTEM_NAME}
        CMAKE_SYSTEM_PROCESSOR:${CMAKE_SYSTEM_PROCESSOR} 
        
        Unsupported platform for rtsan_standalone
    ")
endif()

if(PROJECT_IS_TOP_LEVEL)
    add_executable(rtsan_demo rtsan_demo.cc)
    target_link_libraries(rtsan_demo PRIVATE rtsan::rtsan_standalone)
endif()
