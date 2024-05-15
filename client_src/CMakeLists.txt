project(Jazz)

FILE(GLOB client_src_files "*.cpp" "*.h")

# MESSAGE
message(STATUS "Files in ${PROJECT_SOURCE_DIR}")
foreach(file ${client_src_files})
    message(STATUS "client_src_files: ${file}")
endforeach()

# Add library target
add_library(client_lib STATIC ${client_src_files})

# Add compile options
target_compile_options(client_lib PRIVATE -fPIC)

# Link libraries (if applicable)
target_link_libraries(client_lib common_lib ${SDL2PP_LIBRARIES})