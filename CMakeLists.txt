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

### GLEW ###

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

############

### SOIL ###

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

############

### manymouse ###

set(MANYMOUSE_SOURCE
	external/manymouse/linux_evdev.c
	external/manymouse/macosx_hidmanager.c
	external/manymouse/macosx_hidutilities.c
	external/manymouse/manymouse.c
	external/manymouse/manymouse.h
	external/manymouse/windows_wminput.c
	external/manymouse/x11_xinput2.c
)

add_library(manymouse  STATIC
	${MANYMOUSE_SOURCE}
)

############

include_directories(
	external/glew-2.0.0/include
	external/glfw-3.2.1/include
	external/glm
	external/soil/src
	external/fltk-1.3.4-1
	external/manymouse
	${CMAKE_BINARY_DIR}/external/fltk-1.3.4-1
)


set(ALL_LIBS
	${OPENGL_LIBRARIES}
	soil
	glfw
	GLEW_200
)

add_executable(SDENV2_Project
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
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_Project)

target_link_libraries(SDENV2_Project
	soil
	glfw
  GLEW_200
	fltk
	fltk_forms
	fltk_gl
	fltk_images
	manymouse
)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(SDENV2_Project
		-lGL
	)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

# Xcode and Visual working directories
#set_target_properties(project PROPERTIES XCODE_ATTRIBUTE_CONFIGURATION_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/project/“)
#create_target_launcher(project WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/project/“)


if (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )
#add_custom_command(
#   TARGET project POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_CFG_INTDIR}/project${CMAKE_EXECUTABLE_SUFFIX}" "${CMAKE_CURRENT_SOURCE_DIR}/project/“
#)
elseif (${CMAKE_GENERATOR} MATCHES "Xcode" )

endif (NOT ${CMAKE_GENERATOR} MATCHES "Xcode" )

if (MSVC)
	include(cmake/vsorganizing.cmake)
endif()


# Copy assets to the build directory
file(
	COPY sdenv2/assets
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY sdenv2/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)
