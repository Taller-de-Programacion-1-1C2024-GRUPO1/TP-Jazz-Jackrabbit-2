project(Jazz)

file(GLOB common_src_files "*.cpp" "*.h") 

# MESSAGE
message(STATUS "Files in ${PROJECT_SOURCE_DIR}")
foreach(file ${common_src_files})
    message(STATUS "common_src_files: ${file}")
endforeach()

# Add library target
add_library(common_lib ${common_src_files})

# Add include directories
target_include_directories(common_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

# Link libraries (if applicable)
target_link_libraries(common_lib yaml-cpp)