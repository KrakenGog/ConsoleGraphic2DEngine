file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/KrakenEngine/*.cpp)

include_directories(
./
./RendererSystem 
./SpriteSystem
./Components
./EntityComponentBase
./EntityComponentBase/ComponentIterator
./EntityContainers
./EventSystem
./TestFiles
./UISystem
./Utils
./Math
)

add_executable(KrakenEngine ${SOURCES})
target_compile_options(KrakenEngine PUBLIC  -o3)


set_property(TARGET KrakenEngine PROPERTY CXX_STANDARD 20)