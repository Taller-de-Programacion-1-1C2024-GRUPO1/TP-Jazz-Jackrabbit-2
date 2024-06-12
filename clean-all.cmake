if(EXISTS ${CMAKE_BINARY_DIR}/CMakeCache.txt)
    file(REMOVE ${CMAKE_BINARY_DIR}/CMakeCache.txt)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/CMakeFiles)
    file(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/CMakeFiles)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/Makefile)
    file(REMOVE ${CMAKE_BINARY_DIR}/Makefile)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/CMakeDoxyfile.in)
    file(REMOVE ${CMAKE_BINARY_DIR}/CMakeDoxyfile.in)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/CMakeDoxyfile.in)
    file(REMOVE ${CMAKE_BINARY_DIR}/CMakeDoxyfile.in)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/cmake_install.cmake)
    file(REMOVE ${CMAKE_BINARY_DIR}/cmake_install.cmake)
endif()

if(EXISTS ${CMAKE_BINARY_DIR}/CMakeFiles/cmake.check_cache)
    file(REMOVE ${CMAKE_BINARY_DIR}/CMakeFiles/cmake.check_cache)
endif()
