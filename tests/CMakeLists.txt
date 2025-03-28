add_executable(
  tests
  tests.cpp
  AllocatorTests.cpp
  ../KrakenEngine/EntityComponentBase/ComponentAllocator.cpp
  ../KrakenEngine/EntityComponentBase/Component.cpp
)
target_link_libraries(
  tests
  GTest::gtest_main
)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)
include(GoogleTest)
include_directories(../KrakenEngine)

gtest_discover_tests(tests)