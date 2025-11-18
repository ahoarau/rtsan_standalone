cmake_minimum_required(VERSION 3.22)

project(rtsan_standalone VERSION 1.0.0 LANGUAGES CXX)

add_library(rtsan::rtsan_standalone STATIC IMPORTED)
set_target_properties(rtsan::rtsan_standalone PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/linux-x86_64/libclang_rt.rtsan.a
)
target_include_directories(rtsan::rtsan_standalone INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(rtsan::rtsan_standalone INTERFACE -fsanitize=realtime)
target_link_options(rtsan::rtsan_standalone INTERFACE -fsanitize=realtime)

if(PROJECT_IS_TOP_LEVEL)
    add_executable(rtsan_demo rtsan_demo.cc)
    target_link_libraries(rtsan_demo PRIVATE rtsan::rtsan_standalone)
endif()
