#
#
cmake_minimum_required(VERSION 3.5)
project(rc8server)

add_compile_options( -Wno-write-strings -fcompare-debug-second -g)

find_package(yaml-cpp REQUIRED)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/orin_bcap.cmake)
message("ORIN_SERVER_LIB: ${ORIN_SERVER_LIBRARIES}")
#
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
	${YAML_CPP_LIBRARIES}
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

