cmake_minimum_required(VERSION 3.10)
project(Client)

set(CMAKE_CXX_STANDARD 14)

set(SOURCES
    src/Client.cpp
    src/Main.cpp
)

set(HEADERS
    include/Client.h
)

add_executable(Client ${SOURCES} ${HEADERS})