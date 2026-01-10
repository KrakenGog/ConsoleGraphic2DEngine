cmake_minimum_required(VERSION 3.18)

project(KrakenEngine)

enable_testing()

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(external)
add_subdirectory(KrakenEngine)
add_subdirectory(tests)
add_subdirectory(ClientCode)



