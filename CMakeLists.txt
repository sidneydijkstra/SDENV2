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

### FREETYPE ###

include_directories(external/freetype2/include)

set(FREETYPE_SOURCE
  external/freetype2/include/freetype/config/ftconfig.h
  external/freetype2/include/freetype/config/ftheader.h
  external/freetype2/include/freetype/config/ftmodule.h
  external/freetype2/include/freetype/config/ftoption.h
  external/freetype2/include/freetype/config/ftstdlib.h
  external/freetype2/include/freetype/freetype.h
  external/freetype2/include/freetype/ftadvanc.h
  external/freetype2/include/freetype/ftautoh.h
  external/freetype2/include/freetype/ftbbox.h
  external/freetype2/include/freetype/ftbdf.h
  external/freetype2/include/freetype/ftbitmap.h
  external/freetype2/include/freetype/ftbzip2.h
  external/freetype2/include/freetype/ftcache.h
  external/freetype2/include/freetype/ftcffdrv.h
  external/freetype2/include/freetype/ftchapters.h
  external/freetype2/include/freetype/ftcid.h
  external/freetype2/include/freetype/fterrdef.h
  external/freetype2/include/freetype/fterrors.h
  external/freetype2/include/freetype/ftfntfmt.h
  external/freetype2/include/freetype/ftgasp.h
  external/freetype2/include/freetype/ftglyph.h
  external/freetype2/include/freetype/ftgxval.h
  external/freetype2/include/freetype/ftgzip.h
  external/freetype2/include/freetype/ftimage.h
  external/freetype2/include/freetype/ftincrem.h
  external/freetype2/include/freetype/ftlcdfil.h
  external/freetype2/include/freetype/ftlist.h
  external/freetype2/include/freetype/ftlzw.h
  external/freetype2/include/freetype/ftmac.h
  external/freetype2/include/freetype/ftmm.h
  external/freetype2/include/freetype/ftmodapi.h
  external/freetype2/include/freetype/ftmoderr.h
  external/freetype2/include/freetype/ftotval.h
  external/freetype2/include/freetype/ftoutln.h
  external/freetype2/include/freetype/ftpfr.h
  external/freetype2/include/freetype/ftrender.h
  external/freetype2/include/freetype/ftsizes.h
  external/freetype2/include/freetype/ftsnames.h
  external/freetype2/include/freetype/ftstroke.h
  external/freetype2/include/freetype/ftsynth.h
  external/freetype2/include/freetype/ftsystem.h
  external/freetype2/include/freetype/fttrigon.h
  external/freetype2/include/freetype/ftttdrv.h
  external/freetype2/include/freetype/fttypes.h
  external/freetype2/include/freetype/ftwinfnt.h
  external/freetype2/include/freetype/internal/autohint.h
  external/freetype2/include/freetype/internal/ftcalc.h
  external/freetype2/include/freetype/internal/ftdebug.h
  external/freetype2/include/freetype/internal/ftdriver.h
  external/freetype2/include/freetype/internal/ftgloadr.h
  external/freetype2/include/freetype/internal/fthash.h
  external/freetype2/include/freetype/internal/ftmemory.h
  external/freetype2/include/freetype/internal/ftobjs.h
  external/freetype2/include/freetype/internal/ftpic.h
  external/freetype2/include/freetype/internal/ftrfork.h
  external/freetype2/include/freetype/internal/ftserv.h
  external/freetype2/include/freetype/internal/ftstream.h
  external/freetype2/include/freetype/internal/fttrace.h
  external/freetype2/include/freetype/internal/ftvalid.h
  external/freetype2/include/freetype/internal/internal.h
  external/freetype2/include/freetype/internal/psaux.h
  external/freetype2/include/freetype/internal/pshints.h
  external/freetype2/include/freetype/internal/services/svbdf.h
  external/freetype2/include/freetype/internal/services/svcid.h
  external/freetype2/include/freetype/internal/services/svfntfmt.h
  external/freetype2/include/freetype/internal/services/svgldict.h
  external/freetype2/include/freetype/internal/services/svgxval.h
  external/freetype2/include/freetype/internal/services/svkern.h
  external/freetype2/include/freetype/internal/services/svmm.h
  external/freetype2/include/freetype/internal/services/svotval.h
  external/freetype2/include/freetype/internal/services/svpfr.h
  external/freetype2/include/freetype/internal/services/svpostnm.h
  external/freetype2/include/freetype/internal/services/svprop.h
  external/freetype2/include/freetype/internal/services/svpscmap.h
  external/freetype2/include/freetype/internal/services/svpsinfo.h
  external/freetype2/include/freetype/internal/services/svsfnt.h
  external/freetype2/include/freetype/internal/services/svttcmap.h
  external/freetype2/include/freetype/internal/services/svtteng.h
  external/freetype2/include/freetype/internal/services/svttglyf.h
  external/freetype2/include/freetype/internal/services/svwinfnt.h
  external/freetype2/include/freetype/internal/sfnt.h
  external/freetype2/include/freetype/internal/t1types.h
  external/freetype2/include/freetype/internal/tttypes.h
  external/freetype2/include/freetype/t1tables.h
  external/freetype2/include/freetype/ttnameid.h
  external/freetype2/include/freetype/tttables.h
  external/freetype2/include/freetype/tttags.h
  external/freetype2/include/freetype/ttunpat.h
  external/freetype2/include/ft2build.h
)

add_library(freetype STATIC
  ${FREETYPE_SOURCE}
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

include_directories(
	external/glew-2.0.0/include
	external/glfw-3.2.1/include
	external/glm
	external/soil/src
	external/fltk-1.3.4-1
	${CMAKE_BINARY_DIR}/external/fltk-1.3.4-1
)


set(ALL_LIBS
	${OPENGL_LIBRARIES}
	soil
	glfw
	GLEW_200
  freetype
)

# engine #

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
)

target_link_libraries(SDENV2
	${ALL_LIBS}
)

# start project #

add_executable(SDENV2_start
  start/main.cpp
  start/myscene.cpp
  start/myscene.h
  start/myentity.cpp
  start/myentity.h
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_start)

target_link_libraries(SDENV2_start
	soil
	glfw
  GLEW_200
	fltk
	fltk_forms
	fltk_gl
	fltk_images
  freetype
  SDENV2
)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
	target_link_libraries(SDENV2_start
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



# Copy assets to the build directory
file(
	COPY sdenv2/assets
	DESTINATION ${CMAKE_BINARY_DIR}
)
file(
	COPY sdenv2/shaders
	DESTINATION ${CMAKE_BINARY_DIR}
)
