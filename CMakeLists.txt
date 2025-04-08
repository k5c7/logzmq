cmake_minimum_required(VERSION 3.16)

project(logzmq LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(logzmq main.cpp
    logger.h logger.cpp)

target_compile_options(logzmq PRIVATE -Wall)
target_compile_options(logzmq PRIVATE -Werror)

target_link_libraries(logzmq PRIVATE zmq)

include(GNUInstallDirs)
install(TARGETS logzmq
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
