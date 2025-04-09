cmake_minimum_required(VERSION 3.16)

project(logzmq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message("System: " ${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_VERSION})
message("Processor: " ${CMAKE_CXX_COMPILER_ARCHITECTURE_ID})
message("Compiler: " ${CMAKE_CXX_COMPILER_ID} " " ${CMAKE_CXX_COMPILER_VERSION})

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
    set(VCPKG_TARGET_TRIPLET "x64-windows")
endif()

add_executable(publisher
    zmq_publisher.cpp
    logger.h
    logger.cpp)

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    find_package(cppzmq CONFIG REQUIRED)
    target_link_libraries(publisher PRIVATE cppzmq)
else()
    target_link_libraries(publisher PRIVATE zmq)
    target_compile_options(publisher PRIVATE -Wall)
    target_compile_options(publisher PRIVATE -Werror)
endif()


include(GNUInstallDirs)
install(TARGETS publisher
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
