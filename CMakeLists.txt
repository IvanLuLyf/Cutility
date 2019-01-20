cmake_minimum_required(VERSION 3.8)
project(Cutility)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES main.c ArrayList.h Common.h LinkedList.h List.h)
add_executable(Cutility ${SOURCE_FILES})