cmake_minimum_required(VERSION 3.18)

project(KrakenEngine)
file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/KrakenEngine/*.cpp)
       
     
include_directories(
./KrakenEngine/
./KrakenEngine/RendererSystem 
./KrakenEngine/SpriteSystem
./KrakenEngine/Components
./KrakenEngine/EntityComponentBase
./KrakenEngine/EventSystem
./KrakenEngine/TestFiles
./KrakenEngine/UISystem
./KrakenEngine/Utils
)
add_executable(KrakenEngine ${SOURCES})

set_property(TARGET KrakenEngine PROPERTY CXX_STANDARD 20)