cmake_minimum_required(VERSION 3.22)

project(rtsan_standalone VERSION 1.0.0 LANGUAGES C CXX)

add_library(rtsan_standalone INTERFACE)
target_include_directories(rtsan_standalone INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(rtsan_standalone INTERFACE 
    $<$<PLATFORM_ID:Darwin>:${CMAKE_CURRENT_SOURCE_DIR}/macos/libclang_rt.rtsan_osx_dynamic.dylib>
    $<$<PLATFORM_ID:Linux>:${CMAKE_CURRENT_SOURCE_DIR}/linux/libclang_rt.rtsan_linux_${CMAKE_SYSTEM_PROCESSOR}.a>
)

if(PROJECT_IS_TOP_LEVEL)
    add_executable(rtsan_demo rtsan_demo.cc)
    target_link_libraries(rtsan_demo PRIVATE rtsan_standalone)
    if(NOT WIN32)
        target_compile_definitions(rtsan_demo PRIVATE __SANITIZE_REALTIME)
    endif()
endif()
