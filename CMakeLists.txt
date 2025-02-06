cmake_minimum_required(VERSION 3.18)

project(KrakenEngine)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/KrakenEngine/*.cpp)
       
     
include_directories(
./KrakenEngine/
./KrakenEngine/RendererSystem 
./KrakenEngine/SpriteSystem
./KrakenEngine/Components
./KrakenEngine/EntityComponentBase
./KrakenEngine/EntityComponentBase/ComponentIterator
./KrakenEngine/EntityContainers
./KrakenEngine/EventSystem
./KrakenEngine/TestFiles
./KrakenEngine/UISystem
./KrakenEngine/Utils
./KrakenEngine/Math
)
add_executable(KrakenEngine ${SOURCES})
target_compile_options(KrakenEngine PUBLIC  -o3)

#set(CMAKE_CXX_COMPILER C:/msys64/ucrt64/bin/g++)
#set(CMAKE_C_COMPILER C:/msys64/ucrt64/bin/gcc)

#add_definitions(-std=c++20)
set_property(TARGET KrakenEngine PROPERTY CXX_STANDARD 20)
