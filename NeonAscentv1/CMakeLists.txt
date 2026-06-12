cmake_minimum_required(VERSION 3.14)
project(NeonAscent LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#lokalnie
if(EXISTS "C:/SFML-2.6.1/lib/cmake/SFML")
    set(SFML_DIR "C:/SFML-2.6.1/lib/cmake/SFML")
endif()

#globalne ustawienie (jak nie dziala to trzeba zmienic #lokalnie na swoja sciezke)
find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

#pliki wykonawcze
add_executable(NeonAscent
    main.cpp
    Gracz.h
    Platforma.h
    Gra.h
    Obiekt.h
    Gra.cpp
    Gracz.cpp
    Platforma.cpp



)
add_custom_command(
    TARGET NeonAscent POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_CURRENT_SOURCE_DIR}/media"
    "$<TARGET_FILE_DIR:NeonAscent>/media"
)

#sfml
target_link_libraries(NeonAscent PRIVATE sfml-graphics sfml-window sfml-system)