#
#   ORiN Server 
find_file(ORIN_LIB NAME libbcap_server.a PATHS "/usr/local/ros/*")
if (ORIN_LIB)
  set(ORIN_SERVER_LIBRARIES ${ORIN_LIB} pthread)
  message(STATUS "orin_bcap library: ${ORIN_LIB}")
else()
  message(FATAL_ERROR "orin_bcap server library not found")
endif()

find_path(ORIN_INC bCAPServer/bcap_server.h PATHS "/usr/local/ros/include/*")
if (ORIN_INC)
  set(ORIN_INCLUDE_PATH ${ORIN_INC})
  message(STATUS "orin_bcap headers: ${ORIN_INC}")
else()
  message(FATAL_ERROR "header file of orin_bcap server not found")
endif()
###############

