# CMakeList.txt : CMake project for CppLearning, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CppLearning")

# Add source to this project's executable.
add_executable (CppLearning "CppLearning.cpp" "CppLearning.h" "Utility/option.h" "Utility/option.cpp" "Utility/value.h" "Utility/value.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CppLearning PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
