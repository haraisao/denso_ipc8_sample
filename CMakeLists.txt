#
#
cmake_minimum_required(VERSION 3.5)
project(rc8server)

#add_compile_options( -Wno-write-strings -fcompare-debug-second -g )
add_compile_options( -Wno-write-strings -fcompare-debug-second )
#string(REPLACE ":" ";" CMAKE_PREFIX_PATH $ENV{AMENT_PREFIX_PATH})

find_package(yaml-cpp REQUIRED)

#
#   ORiN Server 
find_file(ORIN_LIB NAME libbcap_server.a PATHS "/usr/local/ros/*")
if (ORIN_LIB)
  set(ORIN_SERVER_LIBRARIES ${ORIN_LIB} pthread)
  message("-- FOUND: ${ORIN_LIB}")
else()
  message("Not FOUND")
endif()

find_path(ORIN_INC bCAPServer/bcap_server.h PATHS "/usr/local/ros/include/*")
if (ORIN_INC)
  set(ORIN_INCLUDE_PATH ${ORIN_INC})
  message("-- FOUND: ${ORIN_INC}")
else()
  message("Not FOUND")
endif()
###############

include_directories(
  ${ORIN_INCLUDE_PATH}
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

#
#
add_executable(${PROJECT_NAME}
   src/Server.cpp
   src/Variables.cpp
   src/PrintVariant.cpp
   src/NotUseFunc.cpp
   src/FileSystem.cpp
)

target_link_libraries(${PROJECT_NAME} 
	${ORIN_SERVER_LIBRARIES}
	${YAML_CPP_LIBRARIES})

#
# INSTALL
# 
install(TARGETS ${PROJECT_NAME} 
  #  LIBRARY DESTINATION lib
  #  ARCHIVE DESTINATION lib
  #  RUNTIME DESTINATION lib
  DESTINATION lib/${PROJECT_NAME}
)

