add_executable(
  tests
  tests.cpp
  AllocatorTests.cpp
  ../KrakenEngine/EntityComponentBase/ComponentAllocator.cpp
  ../KrakenEngine/EntityComponentBase/Component.cpp
  "ComponentContainerTests.cpp")
target_link_libraries(
  tests
  GTest::gtest_main
  sigslot
)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)
include(GoogleTest)
include_directories(../KrakenEngine)

gtest_discover_tests(tests)