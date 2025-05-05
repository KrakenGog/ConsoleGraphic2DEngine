file(GLOB_RECURSE GAME_SOURCE ${PROJECT_SOURCE_DIR}/ClientCode/*.cpp)

add_executable(game ${GAME_SOURCE} "ClientEntryPoint.cpp")

target_include_directories(game PRIVATE 
	./
)


target_compile_options(game PUBLIC  -O3)
target_link_libraries(game PRIVATE KrakenEngine)


set_property(TARGET game PROPERTY CXX_STANDARD 20)