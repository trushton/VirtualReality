
cmake_minimum_required(VERSION 2.8)

project(VR_Lib)

set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "$ENV{CAVR_BUILD_PATH}/CMakeModules")

find_package(Lua51 REQUIRED)
find_package(GLOG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(UNIX)
	add_definitions(-DUNIX)
endif(UNIX)


include_directories(
	"${LUA_INCLUDE_DIR}"
	"$ENV{CAVR_HOME_PATH}/cavr/include"
	"$ENV{CAVR_HOME_PATH}/extensions/gfx/include"
	"$ENV{CAVR_HOME_PATH}/extensions/gl/include"
	"$ENV{CAVR_BUILD_PATH}/IrrKlang/include"
    "${PROJECT_SOURCE_DIR}/include"
	"${GLOG_INCLUDE_DIRS}"
)

link_directories(
	"$ENV{CAVR_BUILD_PATH}/IrrKlang/lib"
	"$ENV{CAVR_HOME_PATH}/build/cavr"
	"$ENV{CAVR_HOME_PATH}/build/extensions/gl"
	"$ENV{CAVR_HOME_PATH}/build/extensions/gfx"
)

#MESSAGE( STATUS "FILES: " ${INCLUDES} )
include_directories("include")
include_directories("include/shapes")

aux_source_directory("src" vr_SRC)

add_library(vr SHARED ${vr_SRC})
target_link_libraries(vr cavr cavrgl cavrgfx IrrKlang ${GLOG_LIBRARIES} ${OPENGL_LIBRARY} ${GLEW_LIBRARIES})