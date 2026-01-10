file(GLOB_RECURSE SOURCES ${PROJECT_SOURCE_DIR}/KrakenEngine/*.cpp)

add_library(KrakenEngine ${SOURCES})


target_include_directories(KrakenEngine PUBLIC
./
./RendererSystem 
./SpriteSystem
./PhysicsSystem
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

target_link_libraries(KrakenEngine PRIVATE box2d)
target_link_libraries(KrakenEngine PUBLIC Pal::Sigslot)
get_target_property(INCLUDE_DIRS KrakenEngine INCLUDE_DIRECTORIES)
message("Include path: ${INCLUDE_DIRS}")
set_property(TARGET KrakenEngine PROPERTY CXX_STANDARD 20)