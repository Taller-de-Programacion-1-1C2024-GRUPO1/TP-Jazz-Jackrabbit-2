project(Jazz)

# Buscar paquetes de Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

FILE(GLOB client_src_files "*.cpp"  "*.h")
FILE(GLOB qt_src_files "/QT/*.cpp" "/QT/*.h" "/QT/*.ui")


# PREGUNTAR
#add_definitions(-DCHARACTERS_PATH="${PROJECT_SOURCE_DIR}/client_src/resources/characters")

#Messages
message(STATUS "Files in ${PROJECT_SOURCE_DIR}")
foreach(file ${client_src_files})
    message(STATUS "client_src_files: ${file}")
endforeach()
foreach(file ${qt_src_files})
    message(STATUS "qt_src_files: ${file}")
endforeach()

#add_subdirectory(QT)
add_library(client_lib STATIC ${client_src_files} ${qt_src_files})
target_compile_options(client_lib PRIVATE -fPIC)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++17")
#target_include_directories(client_lib PRIVATE QT)
target_link_libraries(client_lib common_lib ${SDL2PP_LIBRARIES} Qt5::Widgets)



