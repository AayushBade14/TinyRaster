cmake_minimum_required(VERSION 3.10)
project(
  tr
  VERSION 1.0
  DESCRIPTION "TinyRaster - custom software rasterizer"
  LANGUAGES C CXX
)

set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")

add_library(
  Framebuffer
  STATIC
  ./Framebuffer.cpp
)

add_executable(
  tr
  main.cpp
)
target_link_libraries(
  tr
  PUBLIC
  Framebuffer
)

target_compile_definitions(
  tr
  PRIVATE
  $<$<CONFIG:DEBUG>:DEBUG>
)

