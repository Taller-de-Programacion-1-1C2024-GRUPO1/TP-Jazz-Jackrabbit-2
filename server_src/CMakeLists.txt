project(Jazz)
FILE(GLOB server_src_files "*.cpp" "*.h")

# MESSAGE
message(STATUS "Files in ${PROJECT_SOURCE_DIR}")
foreach(file ${server_src_files})
    message(STATUS "server_src_files: ${file}")
endforeach(file)

# Add library target
add_library(server_lib STATIC ${server_src_files})

# Link libraries (if applicable)
target_link_libraries(server_lib common_lib game_lib)