CMAKE_MINIMUM_REQUIRED(VERSION 3.14)
PROJECT(Project)

# Main props
SET(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -O0")
SET(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O3")

# =================================
# Google test
# =================================
INCLUDE(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
SET(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
   
ENABLE_TESTING()

# Target 
SET(_target "AccumulatorTest")

ADD_EXECUTABLE(
  ${_target}
  AccumulatorTest.cpp
  UniqueAccumulatorTest.cpp
)
TARGET_LINK_LIBRARIES(
  ${_target}
  GTest::gtest_main
)

INCLUDE(GoogleTest)
gtest_discover_tests(${_target})
