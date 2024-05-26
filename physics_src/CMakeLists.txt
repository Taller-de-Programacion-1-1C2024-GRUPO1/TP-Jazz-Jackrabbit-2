project(Jazz)

file(GLOB physics_src_files "*.cpp" "*.h")

# MESSAGE
message(STATUS "Files in ${PROJECT_SOURCE_DIR}")
foreach(file ${physics_src_files})
    message(STATUS "game_src_files: ${file}")
endforeach()

# Add library target
add_library(physics_lib ${physics_src_files})

# Add include directories
target_include_directories(physics_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Link libraries (if applicable)
target_link_libraries(physics_lib common_lib)