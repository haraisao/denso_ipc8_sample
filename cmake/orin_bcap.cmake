#
#   ORiN Server 

if(orin_bcap_DIR)
  set(BCAP_INCLUDE_PATH "${orin_bcap_DIR}/../../../include/orin_bcap")
  set(BCAP_LIB_PATH "${orin_bcap_DIR}/../../../lib")
  link_directories(BEFORE ${BCAP_LIB_PATH})
  set(BCAP_SERVER_LIBRARIES bcap_server pthread)
else()
  find_file(BCAP_LIB NAME libbcap_server.a PATHS "/usr/local/ros/*")
  if (BCAP_LIB)
    set(BCAP_SERVER_LIBRARIES ${BCAP_LIB} pthread)
    message(STATUS "orin_bcap library: ${BCAP_LIB}")
  else()
    message(FATAL_ERROR "orin_bcap server library not found")
  endif()

  find_path(BCAP_INC bCAPServer/bcap_server.h PATHS "/usr/local/ros/include/*")
  if (BCAP_INC)
    set(BCAP_INCLUDE_PATH ${BCAP_INC})
    message(STATUS "orin_bcap headers: ${BCAP_INC}")
  else()
    message(FATAL_ERROR "header file of orin_bcap server not found")
  endif()
endif()
###############

