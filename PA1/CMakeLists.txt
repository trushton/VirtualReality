CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(Example)

SET(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH}" "$ENV{CAVR_BUILD_PATH}/CMakeModules")

FIND_PACKAGE(Lua51 REQUIRED)
FIND_PACKAGE(GLOG REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)

#SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
SET(CXX11_FLAGS -std=gnu++11)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${CXX11_FLAGS}")

IF(UNIX)
	ADD_DEFINITIONS(-DUNIX)
ENDIF(UNIX)


INCLUDE_DIRECTORIES(
	"${LUA_INCLUDE_DIR}"
	"$ENV{CAVR_HOME_PATH}/cavr/include"
	"$ENV{CAVR_HOME_PATH}/extensions/gfx/include"
	"$ENV{CAVR_HOME_PATH}/extensions/gl/include"
	"$ENV{CAVR_BUILD_PATH}/IrrKlang/include"
  "${PROJECT_SOURCE_DIR}/include"
	"${GLOG_INCLUDE_DIRS}"
)

LINK_DIRECTORIES(
	"$ENV{CAVR_BUILD_PATH}/IrrKlang/lib"
	"$ENV{CAVR_HOME_PATH}/build/cavr" 
	"$ENV{CAVR_HOME_PATH}/build/extensions/gl" 
	"$ENV{CAVR_HOME_PATH}/build/extensions/gfx"
)

# Set Includes
SET(INCLUDES ${PROJECT_SOURCE_DIR}/include)
#MESSAGE( STATUS "FILES: " ${INCLUDES} )
INCLUDE_DIRECTORIES(${INCLUDES})

# Set sources
file(GLOB_RECURSE SOURCES "source/*.cpp")
ADD_EXECUTABLE(Example ${SOURCES})

add_custom_target(BUILD_SUCCESSFUL ALL
                  DEPENDS Example
                  COMMAND ${CMAKE_COMMAND} -E echo ""
                  COMMAND ${CMAKE_COMMAND} -E echo "====================="
                  COMMAND ${CMAKE_COMMAND} -E echo "  Compile complete!"
                  COMMAND ${CMAKE_COMMAND} -E echo "====================="
                  COMMAND ${CMAKE_COMMAND} -E echo "${CMAKE_CURRENT_BINARY_DIR}"
		  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/config
                  COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/shaders/ ${CMAKE_CURRENT_BINARY_DIR}/shaders
		              COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/media/ ${CMAKE_CURRENT_BINARY_DIR}/media
                  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config/example.lua ${CMAKE_CURRENT_BINARY_DIR}/config
                  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config/cavrconfig.lua ${CMAKE_CURRENT_BINARY_DIR}
                  COMMAND ${CMAKE_COMMAND} -E copy ${PROJECT_SOURCE_DIR}/config/cavrplugins.lua ${CMAKE_CURRENT_BINARY_DIR}
                 )

TARGET_LINK_LIBRARIES(Example cavr cavrgl cavrgfx IrrKlang ${GLOG_LIBRARIES} ${OPENGL_LIBRARY} ${GLEW_LIBRARIES})
