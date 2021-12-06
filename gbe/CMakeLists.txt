# CMakeList.txt : CMake project for gbe, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (gbe "gbe.cpp"  "cpu.cpp" "cpu.h" "bus.h" "bus.cpp" "register.h" "register.cpp")

# TODO: Add tests and install targets if needed.
