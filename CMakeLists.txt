cmake_minimum_required(VERSION 3.22)

project(rtsan_standalone VERSION 1.0.0 LANGUAGES CXX)

if(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    add_library(rtsan::rtsan_standalone SHARED IMPORTED GLOBAL)
    target_include_directories(rtsan::rtsan_standalone INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_compile_options(rtsan::rtsan_standalone INTERFACE -Wfunction-effects)
    target_compile_options(rtsan::rtsan_standalone INTERFACE -Wperf-constraint-implies-noexcept)
    target_compile_options(rtsan::rtsan_standalone INTERFACE -fsanitize=realtime)
    target_link_options(rtsan::rtsan_standalone INTERFACE -fsanitize=realtime)
    set_target_properties(rtsan::rtsan_standalone PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/macos/libclang_rt.rtsan_osx_dynamic.dylib
    )
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_library(rtsan::rtsan_standalone STATIC IMPORTED GLOBAL)
    target_include_directories(rtsan::rtsan_standalone INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    target_compile_options(rtsan::rtsan_standalone INTERFACE -Wfunction-effects)
    target_compile_options(rtsan::rtsan_standalone INTERFACE -Wperf-constraint-implies-noexcept)
    target_compile_options(rtsan::rtsan_standalone INTERFACE -fsanitize=realtime)
    target_link_options(rtsan::rtsan_standalone INTERFACE -fsanitize=realtime)
    set_target_properties(rtsan::rtsan_standalone PROPERTIES
        IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/linux/libclang_rt.rtsan_linux_${CMAKE_SYSTEM_PROCESSOR}.a
    )
else()
    add_library(rtsan::rtsan_standalone UNKNOWN IMPORTED GLOBAL)
    message(WARNING "
        CMAKE_SYSTEM_NAME:${CMAKE_SYSTEM_NAME}
        CMAKE_SYSTEM_PROCESSOR:${CMAKE_SYSTEM_PROCESSOR} 
        
        Unsupported platform for rtsan_standalone
    ")
endif()

if(PROJECT_IS_TOP_LEVEL)
    add_executable(rtsan_demo rtsan_demo.cc)
    target_link_libraries(rtsan_demo PRIVATE rtsan::rtsan_standalone)
endif()
