#
#
cmake_minimum_required(VERSION 3.5)
project(rc8server)

add_compile_options( -Wno-write-strings -fcompare-debug-second -g)

find_package(yaml-cpp REQUIRED)
find_package(Eigen3 REQUIRED)
find_package(orin_bcap)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/orin_bcap.cmake)
message("BCAP_SERVER_LIB: ${BCAP_SERVER_LIBRARIES}")
#set(BCAP_INCLUDE_PATH "${orin_bcap_DIR}/../../../include/orin_bcap")
#set(BCAP_SERVER_LIB_PATH "${orin_bcap_DIR}/../../../lib")
#set(BCAP_SERVER_LIBRARIES "bcap_server")
message("orin_bcap: ${BCAP_INCLUDE_PATH}")
#
include_directories(
  ${BCAP_INCLUDE_PATH}
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

target_link_directories(${PROJECT_NAME} PUBLIC
  ${BCAP_SERVER_LIB_PATH}
)

target_link_libraries(${PROJECT_NAME} 
  ${BCAP_SERVER_LIBRARIES}
  ${YAML_CPP_LIBRARIES}
  Eigen3::Eigen
)

#
# INSTALL
# 
install(TARGETS ${PROJECT_NAME} 
	DESTINATION ${PROJECT_NAME}/bin
)

install(PROGRAMS  scripts/start.sh
	DESTINATION ${PROJECT_NAME}/bin
)

install(DIRECTORY config
	DESTINATION ${PROJECT_NAME}
)

