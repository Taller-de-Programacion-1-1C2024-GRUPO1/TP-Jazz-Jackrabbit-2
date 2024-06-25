project(JazzClient)

# Buscar paquetes de Qt5
find_package(Qt5 COMPONENTS Widgets REQUIRED)

# Activar AUTOUIC, AUTOMOC y AUTORCC
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB client_src_files "*.cpp" "*.h")
file(GLOB qt_src_files "QT/*.cpp" "QT/*.h" "QT/*.ui")

# Incluye el archivo de recursos
set(qrc_files QT/resources.qrc)

# Messages
message(STATUS "Files in ${PROJECT_SOURCE_DIR}")
foreach(file ${client_src_files})
    message(STATUS "client_src_files: ${file}")
endforeach()
foreach(file ${qt_src_files})
    message(STATUS "qt_src_files: ${file}")
endforeach()


add_library(client_lib STATIC ${client_src_files} ${qt_src_files} ${qrc_files})
target_compile_options(client_lib PRIVATE -fPIC)
set(CMAKE_CXX_FLAGS "-Wall -fPIC -std=c++17")

target_link_libraries(client_lib common_lib ${SDL2PP_LIBRARIES} Qt5::Widgets)



