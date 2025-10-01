message(STATUS "Conan: Using CMakeDeps conandeps_legacy.cmake aggregator via include()")
message(STATUS "Conan: It is recommended to use explicit find_package() per dependency instead")

find_package(glfw3)
find_package(opengl-registry)
find_package(opengl_system)

set(CONANDEPS_LEGACY  glfw  opengl-registry::opengl-registry  opengl::opengl )