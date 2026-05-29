###############################################################################

cmake_minimum_required (VERSION 3.9.5)

project(app)

# app binary output folders
set(RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_STANDARD 17)

# Add include directories
include_directories("${PROJECT_SOURCE_DIR}")

# Include all source files into the project
file(GLOB_RECURSE ${PROJECT_NAME}_SRCFILES
	"${PROJECT_SOURCE_DIR}/src/*.h"
	"${PROJECT_SOURCE_DIR}/src/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/sys/*.cpp"
	"${PROJECT_SOURCE_DIR}/src/sys/*.hpp"
	"${PROJECT_SOURCE_DIR}/man/*.cpp"
	"${PROJECT_SOURCE_DIR}/man/*.h"
	"${PROJECT_SOURCE_DIR}/lib/tinyPTC/src/*.h"
	"${PROJECT_SOURCE_DIR}/lib/tinyPTC/src/*.c"
	"${PROJECT_SOURCE_DIR}/lib/picoPNG/src/*.hpp"
	"${PROJECT_SOURCE_DIR}/lib/picoPNG/src/*.cpp"

)

# Executable to be produced with required libraries
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRCFILES})
target_link_libraries(${PROJECT_NAME} ncurses X11 Xext)
#target_link_libraries(${PROJECT_NAME} ncurses X11 Xext src lib)
# Requiered compiler features
target_compile_features(${PROJECT_NAME} PRIVATE cxx_range_for)
