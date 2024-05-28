cmake_minimum_required(VERSION 3.12)

project(Jazz
    VERSION 0.0.1
    DESCRIPTION "Jazz JackRabbit 2 GAME")

# Buscar paquetes de Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# SDL2pp configurations
set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory(client_src/SDL2pp)
include_directories(${SDL2PP_INCLUDE_DIRS})

add_subdirectory(server_src)
add_subdirectory(client_src)
add_subdirectory(common_src)
add_subdirectory(physics_src)
add_subdirectory(game_src)

add_executable(jazz_server server_main.cpp)
add_executable(jazz_client client_main.cpp)
add_executable(example_sdl client_src/example_sdl.cpp)
add_executable(example_sdl2pp client_src/example_sdl2pp.cpp)

# Vincular bibliotecas necesarias
target_link_libraries(jazz_server common_lib server_lib)
target_link_libraries(jazz_client common_lib client_lib SDL2pp Qt5::Widgets)
target_link_libraries(example_sdl common_lib client_lib SDL2pp)
target_link_libraries(example_sdl2pp common_lib client_lib SDL2pp)

target_include_directories(jazz_client PRIVATE client_src)
target_include_directories(jazz_client PRIVATE common_src)
target_include_directories(example_sdl PRIVATE common_src)
target_include_directories(example_sdl2pp PRIVATE common_src)

set_target_properties(jazz_client PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

install(TARGETS jazz_client jazz_server example_sdl example_sdl2pp
        RUNTIME DESTINATION /usr/bin
)

install(FILES ${CMAKE_SOURCE_DIR}/external/config/config.yml
        DESTINATION /etc/jazz
)

install(FILES ${CMAKE_SOURCE_DIR}/server_src/config.h
        DESTINATION /etc/jazz
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/client_src
        DESTINATION /var/jazz
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/server_src
        DESTINATION /var/jazz
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/common_src
        DESTINATION /var/jazz
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/external
        DESTINATION /var/jazz
)
#PARA TESTS

#install(DIRECTORY ${CMAKE_SOURCE_DIR}/tests
#        DESTINATION /var/jazz
#)

#install(DIRECTORY ${CMAKE_SOURCE_DIR}/cmake
#        DESTINATION /var/jazz
#)