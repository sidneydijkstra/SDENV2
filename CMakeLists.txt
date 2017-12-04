# CMake entry point
cmake_minimum_required(VERSION 3.0)
project (sdenv2)

find_package(OpenGL REQUIRED)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like 'build')" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

add_subdirectory(external/fltk-1.3.4-1)

if(UNIX)
	set(CMAKE_CXX_FLAGS "-Wall -std=c++0x -pedantic -O2 -g -pg")
	set(CMAKE_CXX_FLAGS "-Wall -Wstrict-aliasing -std=c++0x -O2")

	set(CMAKE_CXX_FLAGS "-Wall -pthread")
	set(CMAKE_CXX_FLAGS "-Wall -pg -std=c++11 ")
endif(UNIX)

if(WIN32)
	add_definitions(
		-D_SCL_SECURE_NO_WARNINGS
	)
endif(WIN32)
add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

add_subdirectory(external/glfw-3.2.1)

if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	-lGL -lGLU -lXrandr -lXext -lX11 -lrt
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
set(OPENGL_LIBRARY
	${OPENGL_LIBRARY}
	${CMAKE_DL_LIBS}
	${GLFW_LIBRARIES}
)
endif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

############
### GLEW ###
############

set(GLEW_SOURCE
	external/glew-2.0.0/src/glew.c
)

add_library(GLEW_200 STATIC
	${GLEW_SOURCE}
	${GLEW_INCLUDE}
)

target_link_libraries(GLEW_200
	${OPENGL_LIBRARY}
)

#################
### FREETYPE2 ###
#################

set (FREETYPE2_INCLUDE_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/external/freetype-2.8.1
)

add_subdirectory(
  external/freetype-2.8.1
)

############
### SOIL ###
############

set(SOIL_SOURCE
	external/soil/src/image_DXT.c
	external/soil/src/image_DXT.h
	external/soil/src/image_helper.c
	external/soil/src/image_helper.h
	external/soil/src/SOIL.c
	external/soil/src/SOIL.h
	external/soil/src/stbi_DDS_aug.h
	external/soil/src/stbi_DDS_aug_c.h
	external/soil/src/stb_image_aug.c
	external/soil/src/stb_image_aug.h
)

add_library(soil STATIC
	${SOIL_SOURCE}
)

###################
### INCLUDE DIR ###
###################

include_directories(
	external/glew-2.0.0/include
	external/glfw-3.2.1/include
	external/glm
	external/soil/src
	external/fltk-1.3.4-1
	${CMAKE_BINARY_DIR}/external/fltk-1.3.4-1

  # freetype
  ${CMAKE_SOURCE_DIR}/external/freetype-2.8.1/include
  ${CMAKE_SOURCE_DIR}/external/freetype-2.8.1/src
)


set(ALL_LIBS
	${OPENGL_LIBRARIES}
	soil
	glfw
	GLEW_200
  freetype
)

##############
### ENGINE ###
##############

add_library(SDENV2 STATIC
  sdenv2/project/main.cpp
	sdenv2/project/renderer.cpp
	sdenv2/project/renderer.h
	sdenv2/project/shader.cpp
	sdenv2/project/shader.h
	sdenv2/project/mesh.cpp
	sdenv2/project/mesh.h
	sdenv2/project/texture.cpp
	sdenv2/project/texture.h
	sdenv2/project/input.cpp
	sdenv2/project/input.h
	sdenv2/project/camera.cpp
	sdenv2/project/camera.h
	sdenv2/project/scene.cpp
	sdenv2/project/scene.h
	sdenv2/project/scenemanager.cpp
	sdenv2/project/scenemanager.h
	sdenv2/project/light.cpp
	sdenv2/project/light.h
	sdenv2/project/framebuffer.cpp
	sdenv2/project/framebuffer.h
	sdenv2/project/particalsystem.cpp
	sdenv2/project/particalsystem.h
	sdenv2/project/partical.cpp
	sdenv2/project/partical.h
	sdenv2/project/text.cpp
	sdenv2/project/text.h
	sdenv2/project/fontloader.cpp
	sdenv2/project/fontloader.h
	sdenv2/project/color.cpp
	sdenv2/project/color.h
	sdenv2/project/sdenv2config.h
)

target_link_libraries(SDENV2
	${ALL_LIBS}
)

file(
	COPY sdenv2/assets
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY sdenv2/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)

#####################
### START PROJECT ###
#####################

add_executable(SDENV2_start
  start/main.cpp
  start/myscene.cpp
  start/myscene.h
  start/myentity.cpp
  start/myentity.h
)

target_link_libraries(SDENV2_start
  glfw
  SDENV2
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_start)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(SDENV2_start
		-lGL
	)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
