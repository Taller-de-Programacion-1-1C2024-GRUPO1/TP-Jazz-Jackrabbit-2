set(CMAKE_BUILD_WITH_INSTALL_RPATH ON)
cmake_minimum_required(VERSION 3.12)

# set the project name
project(Jazz
    VERSION 0.0.1
    DESCRIPTION "Jazz JackRabbit 2 GAME")

# add the subdirectories
add_subdirectory(server_src)
add_subdirectory(client_src)
add_subdirectory(common_src)
add_subdirectory(game_src)
add_subdirectory(physics_src)

# add SDL2pp
set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory(client_src/SDL2pp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${SDL2PP_INCLUDE_DIRS})

# add the executable
add_executable(jazz_server server_main.cpp)
add_executable(jazz_client client_main.cpp)
add_executable(example_sdl client_src/example_sdl.cpp)

target_include_directories(jazz_client PRIVATE client_src)
target_include_directories(jazz_client PRIVATE common_src)

target_link_libraries(jazz_client common_lib client_lib SDL2pp)
target_link_libraries(jazz_server common_lib pthread server_lib game_lib)
target_link_libraries(example_sdl common_lib client_lib SDL2pp)

set_target_properties(jazz_client PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_FLAGS "-Wall -Werror -fPIC -std=c++17")

install(TARGETS jazz_server jazz_client
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
