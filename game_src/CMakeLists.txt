project(Jazz)

file(GLOB game_src_files "*.cpp" "*.h")
file(GLOB commands_files "commands/*.cpp" "commands/*.h")
file(GLOB entities_src_files "entities/*.cpp" "entities/*.h") 

# MESSAGE
message(STATUS "Files in ${PROJECT_SOURCE_DIR}")
foreach(file ${game_src_files})
    message(STATUS "game_src_files: ${file}")
endforeach()
foreach(file ${commands_files})
    message(STATUS "commands_files: ${file}")
endforeach()
foreach(file ${entities_src_files})
    message(STATUS "commands_files: ${file}")
endforeach()

# Add library target
add_library(game_lib ${game_src_files} ${commands_files} ${entities_src_files})

# Add include directories
target_include_directories(game_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_SOURCE_DIR}/commands" "${CMAKE_CURRENT_SOURCE_DIR}/entities")

# Link libraries (if applicable)
target_link_libraries(game_lib common_lib physics_lib)