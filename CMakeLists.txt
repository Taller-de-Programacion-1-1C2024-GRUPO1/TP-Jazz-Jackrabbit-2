cmake_minimum_required(VERSION 3.12)

project(Jazz
    VERSION 0.0.1
    DESCRIPTION "Jazz JackRabbit 2 GAME")

include(CTest)

option(TESTING "Enable tests: " ON)
if (TESTING)
    add_definitions(-DTESTING)
endif()

if (TESTING)
    find_package(GTest REQUIRED)
    include_directories(${GTEST_INCLUDE_DIRS})
endif()

if(TESTING)
    message("Testings enabled!")
    add_subdirectory(tests)
endif()

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

# Vincular bibliotecas necesarias
target_link_libraries(jazz_server common_lib server_lib)
target_link_libraries(jazz_client common_lib client_lib SDL2pp Qt5::Widgets)

target_include_directories(jazz_client PRIVATE client_src)
target_include_directories(jazz_client PRIVATE common_src)

set_target_properties(jazz_client PROPERTIES POSITION_INDEPENDENT_CODE TRUE)

install(TARGETS jazz_client jazz_server
        RUNTIME DESTINATION /usr/bin
)

install(FILES ${CMAKE_SOURCE_DIR}/external/config/config.yml
        DESTINATION /etc/jazz
)

install(FILES ${CMAKE_SOURCE_DIR}/external/config/client_config.yml
        DESTINATION /etc/jazz
)

install(FILES ${CMAKE_SOURCE_DIR}/external/maps/maps.txt
        DESTINATION /etc/jazz
)

install(FILES ${CMAKE_SOURCE_DIR}/server_src/config.h
        DESTINATION /etc/jazz
)

install(FILES ${CMAKE_SOURCE_DIR}/client_src/client_config.h
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

install(DIRECTORY ${CMAKE_SOURCE_DIR}/external/maps
        DESTINATION /var/jazz
)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/tests
        DESTINATION /var/jazz
)
