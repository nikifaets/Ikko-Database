cmake_minimum_required (VERSION 3.0)
set(CMAKE_BUILD_TYPE Debug)

project (Ikko)

file(GLOB_RECURSE Ikko_SRC

	"src/*.h"
	"src/*.cpp"
)

add_executable(Ikko ${Ikko_SRC})



