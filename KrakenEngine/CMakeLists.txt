file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/KrakenEngine/*.cpp)

add_library(KrakenEngine ${SOURCES})

target_include_directories(KrakenEngine PUBLIC
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


target_compile_options(KrakenEngine PUBLIC  -O3)


set_property(TARGET KrakenEngine PROPERTY CXX_STANDARD 20)