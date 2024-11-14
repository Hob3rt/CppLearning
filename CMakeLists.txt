# CMakeList.txt : CMake project for CppLearning, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("CppLearning")

include_directories(${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}) #将编译器的默认标准库路径加入到项目的头文件搜索路径中，使 IDE 能够识别这些文件。

# Add source to this project's executable.
add_executable (CppLearning "CppLearning.cpp" "CppLearning.h" "Utility/option.h" "Utility/option.cpp" "Utility/value.h" "Utility/value.cpp" "Utility/ini_file.h" "Utility/ini_file.cpp" "Utility/ini_file.h" "Utility/logger.h" "Utility/logger.cpp" "Utility/singleton.h" "stl/vector.h" "Utility/time.h" "Utility/time.cpp" "Utility/String.h" "Utility/String.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET CppLearning PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
