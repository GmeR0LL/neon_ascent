cmake_minimum_required(VERSION 3.16)

project(NeonAscentv1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(NeonAscentv1 main.cpp)

include(GNUInstallDirs)
install(TARGETS NeonAscentv1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
