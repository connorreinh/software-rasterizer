cmake_minimum_required(VERSION 3.15...4.0)

project("Software Rasterizer")

set(CMAKE_CXX_STANDARD 17)

# Emit build/compile_commands.json for clangd / IDE IntelliSense.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SOURCES
    src/cli.cpp
    src/framebuffer.cpp
    src/main.cpp
    src/mesh.cpp
    src/stb_image_write.cpp
)

add_executable(rasterizer ${SOURCES})

target_include_directories(rasterizer PRIVATE third_party)

# `cmake --build build --target format` runs clang-format in place over our
# sources (skips third_party/). No-op if clang-format isn't installed.
find_program(CLANG_FORMAT clang-format)
if(CLANG_FORMAT)
  file(GLOB_RECURSE FORMAT_SOURCES CONFIGURE_DEPENDS src/*.cpp src/*.h)
  add_custom_target(format COMMAND ${CLANG_FORMAT} -i ${FORMAT_SOURCES})
endif()
