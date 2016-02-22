INCLUDE(FindPackageHandleStandardArgs)

FIND_PATH(CAVR_INCLUDE_PATH cavr/system.h)
FIND_LIBRARY(CAVR_LIBRARY_PATH cavr)

file(GLOB_RECURSE HARD_CODE_PATH "/usr/local/cavr/plugins/*.so")

if($ENV{CAVR_PLUGIN_PATH})
file(GLOB_RECURSE PLUGIN_PATH "$ENV{CAVR_PLUGIN_PATH}/*.so")
endif($ENV{CAVR_PLUGIN_PATH})

if(PLUGIN_PATH)

#MESSAGE(STATUS "USING PLUGIN PATH")
SET(CAVR_PLUGIN_PATH ${PLUGIN_PATH})

elseif(HARD_CODE_PATH)
MESSAGE(STATUS "USING HARD CODE PATH ${HARD_CODE_PATH}")
SET(CAVR_PLUGIN_PATH ${HARD_CODE_PATH} )

else(PLUGIN_PATH)
message( FATAL_ERROR "You fail" )

endif(PLUGIN_PATH)


FIND_PACKAGE_HANDLE_STANDARD_ARGS(CAVR DEFAULT_MSG 
                                  CAVR_INCLUDE_PATH 
                                  CAVR_LIBRARY_PATH
				  CAVR_PLUGIN_PATH)

IF(CAVR_FOUND)
  SET(CAVR_INCLUDE_DIRS ${CAVR_INCLUDE_PATH})
  SET(CAVR_LIBRARIES ${CAVR_LIBRARY_PATH} ${CAVR_PLUGIN_PATH})
ENDIF(CAVR_FOUND)
