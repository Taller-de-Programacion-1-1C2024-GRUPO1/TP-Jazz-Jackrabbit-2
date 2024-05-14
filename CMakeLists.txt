cmake_minimum_required(VERSION 3.12)

# set the project name
project(Jazz
    VERSION 0.0.1
    DESCRIPTION "Jazz JackRabbit 2 GAME")

# add the subdirectories
add_subdirectory(server_src)
add_subdirectory(client_src)
add_subdirectory(common_src)

# add the executable
add_executable(jazz_server server_main.cpp)
add_executable(jazz_client client_main.cpp)

target_include_directories(jazz_client PRIVATE client_src)
target_include_directories(jazz_client PRIVATE common_src)

target_link_libraries(jazz_client common_lib client_lib)
target_link_libraries(jazz_server common_lib pthread server_lib)

set_target_properties(jazz_client PROPERTIES POSITION_INDEPENDENT_CODE TRUE)
set(CMAKE_CXX_FLAGS "-Wall -Werror -fPIC -std=c++17")

install(TARGETS jazz_server jazz_client
        RUNTIME DESTINATION /usr/bin
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

