# CMake entry point
option(BUILD_START "build the start directory" ON)
option(BUILD_DEMO "build the demo directory" ON)

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

####################################
### SDNW - netowrking for engine ###
####################################


if(WIN32)
  add_library(SDNW STATIC
    external/sdnw/networkmanager.cpp
    external/sdnw/networkmanager.h
    external/sdnw/networkhandler.cpp
    external/sdnw/networkhandler.h

    external/sdnw/networkaction.cpp
    external/sdnw/networkaction.h
    external/sdnw/package.cpp
    external/sdnw/package.h
    external/sdnw/socket.cpp
    external/sdnw/socket.h
    external/sdnw/tcpclient.cpp
    external/sdnw/tcpclient.h
    external/sdnw/tcpconnection.cpp
    external/sdnw/tcpconnection.h
    external/sdnw/tcplistener.cpp
    external/sdnw/tcplistener.h
    external/sdnw/tcpobject.cpp
    external/sdnw/tcpobject.h
  )

  include_directories(
    ${CMAKE_SOURCE_DIR}/external/sdnw/
  )

  target_link_libraries(SDNW wsock32 ws2_32)
endif()

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
  # normal engine
	sdenv2/project/core.cpp
	sdenv2/project/core.h
	sdenv2/project/renderer.cpp
	sdenv2/project/renderer.h
	sdenv2/project/shader.cpp
	sdenv2/project/shader.h
	sdenv2/project/mesh.cpp
	sdenv2/project/mesh.h
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
	sdenv2/project/text.cpp
	sdenv2/project/text.h
	sdenv2/project/fontloader.cpp
	sdenv2/project/fontloader.h
	sdenv2/project/color.cpp
	sdenv2/project/color.h
	sdenv2/project/sprite.cpp
	sdenv2/project/sprite.h
	sdenv2/project/spriteanimator.cpp
	sdenv2/project/spriteanimator.h
	sdenv2/project/entity.cpp
	sdenv2/project/entity.h
	sdenv2/project/timer.cpp
	sdenv2/project/timer.h
	sdenv2/project/resourcemanager.cpp
	sdenv2/project/resourcemanager.h
	sdenv2/project/texture.cpp
	sdenv2/project/texture.h
	sdenv2/project/line.cpp
	sdenv2/project/line.h
	sdenv2/project/vector2.cpp
	sdenv2/project/vector2.h
	sdenv2/project/savemanager.cpp
	sdenv2/project/savemanager.h
	sdenv2/project/sdenv2config.h
  sdenv2/project/action.h

  # UI engine
  sdenv2/project/ui.h
  sdenv2/project/ui/canvas.cpp
  sdenv2/project/ui/canvas.h
  sdenv2/project/ui/uielement.cpp
  sdenv2/project/ui/uielement.h
  sdenv2/project/ui/uitext.cpp
  sdenv2/project/ui/uitext.h
  sdenv2/project/ui/uicollection.cpp
  sdenv2/project/ui/uicollection.h

  sdenv2/project/ui/debugcanvas.cpp
  sdenv2/project/ui/debugcanvas.h

  sdenv2/project/ui/uibutton.cpp
  sdenv2/project/ui/uibutton.h
  sdenv2/project/ui/uitextfield.cpp
  sdenv2/project/ui/uitextfield.h
  sdenv2/project/ui/uitoggle.cpp
  sdenv2/project/ui/uitoggle.h
  sdenv2/project/ui/uiclickablelist.cpp
  sdenv2/project/ui/uiclickablelist.h
  sdenv2/project/ui/uiimage.cpp
  sdenv2/project/ui/uiimage.h
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

include_directories(
	sdenv2/project
)

#####################
### START PROJECT ###
#####################
IF(BUILD_START)

  add_executable(SDENV2_start
    start/main.cpp
    start/myscene.cpp
    start/myscene.h
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

ENDIF(BUILD_START)

####################
### DEMO PROJECT ###
####################
IF(BUILD_DEMO)

  ####################
  ### MAZE PROJECT ###
  ####################
  add_executable(SDENV2_maze
    demos/maze/main.cpp
    demos/maze/maze.cpp
    demos/maze/maze.h
    demos/maze/cell.cpp
    demos/maze/cell.h
    demos/maze/wall.cpp
    demos/maze/wall.h
  )

  target_link_libraries(SDENV2_maze
    glfw
    SDENV2
  )

  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_maze)

  #####################
  ### SMART ROCKETS ###
  #####################
  add_executable(SDENV2_smart_rockets
    demos/smart_rockets/main.cpp
    demos/smart_rockets/world.cpp
    demos/smart_rockets/world.h
    demos/smart_rockets/rocket.cpp
    demos/smart_rockets/rocket.h
  )

  target_link_libraries(SDENV2_smart_rockets
    glfw
    SDENV2
  )

  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_smart_rockets)

  #################
  ### CUBE WAVE ###
  #################
  add_executable(SDENV2_cube_wave
    demos/cube_wave/main.cpp
    demos/cube_wave/world.cpp
    demos/cube_wave/world.h
    demos/cube_wave/cube.cpp
    demos/cube_wave/cube.h
  )

  target_link_libraries(SDENV2_cube_wave
    glfw
    SDENV2
  )

  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_cube_wave)

  ##########################
  ### NETWORKING PROJECT ###
  ##########################

  if(WIN32) # TODO: add lib that supports some use as winsock2
    add_executable(SDENV2_network_chatting
      demos/network_chatting/main.cpp
      demos/network_chatting/myscene.cpp
      demos/network_chatting/myscene.h
      demos/network_chatting/player.cpp
      demos/network_chatting/player.h
    )

    target_link_libraries(SDENV2_network_chatting
      glfw
      SDENV2
      SDNW
    )

    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_network_chatting)
  endif()

  ###########################
  ### MOVING AND GROOVING ###
  ###########################
  add_executable(SDENV2_mag
    demos/moving_and_grooving/main.cpp
    demos/moving_and_grooving/myscene.cpp
    demos/moving_and_grooving/myscene.h
    demos/moving_and_grooving/collision.cpp
    demos/moving_and_grooving/collision.h
    demos/moving_and_grooving/object.cpp
    demos/moving_and_grooving/object.h
  )

  target_link_libraries(SDENV2_mag
    glfw
    SDENV2
  )

  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_mag)

  #####################
  ### STRATEGY GAME ###
  #####################
  add_executable(SDENV2_strategy_game
    demos/strategy_game/main.cpp
    demos/strategy_game/myscene.cpp
    demos/strategy_game/myscene.h
    demos/strategy_game/player.cpp
    demos/strategy_game/player.h
    demos/strategy_game/map.cpp
    demos/strategy_game/map.h
    demos/strategy_game/tile.cpp
    demos/strategy_game/tile.h
  )

  target_link_libraries(SDENV2_strategy_game
    glfw
    SDENV2
  )

  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_strategy_game)

  ################################
  ### FRAMEBUFFER GAME PROJECT ###
  ################################
  add_executable(SDENV2_framebuffer_game
    demos/framebuffer_game/main.cpp
    demos/framebuffer_game/myscene.cpp
    demos/framebuffer_game/myscene.h
    demos/framebuffer_game/player.cpp
    demos/framebuffer_game/player.h
    demos/framebuffer_game/tile.cpp
    demos/framebuffer_game/tile.h
    demos/framebuffer_game/level.cpp
    demos/framebuffer_game/level.h
    demos/framebuffer_game/enemy.cpp
    demos/framebuffer_game/enemy.h
    demos/framebuffer_game/coin.cpp
    demos/framebuffer_game/coin.h
    demos/framebuffer_game/collider.cpp
    demos/framebuffer_game/collider.h

    # levels
    demos/framebuffer_game/levela.cpp
    demos/framebuffer_game/levela.h

    # UI
    demos/framebuffer_game/hudcanvas.cpp
    demos/framebuffer_game/hudcanvas.h
    demos/framebuffer_game/endcanvas.cpp
    demos/framebuffer_game/endcanvas.h
    demos/framebuffer_game/menucanvas.cpp
    demos/framebuffer_game/menucanvas.h

    demos/framebuffer_game/splashscreen.cpp
    demos/framebuffer_game/splashscreen.h

    # level editor
    demos/framebuffer_game/leveleditor.cpp
    demos/framebuffer_game/leveleditor.h
    demos/framebuffer_game/editortile.cpp
    demos/framebuffer_game/editortile.h
    demos/framebuffer_game/editorcanvas.cpp
    demos/framebuffer_game/editorcanvas.h
    demos/framebuffer_game/editorsaver.cpp
    demos/framebuffer_game/editorsaver.h
  )

  target_link_libraries(SDENV2_framebuffer_game
    glfw
    SDENV2
  )

  set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT SDENV2_framebuffer_game)


  IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
  	target_link_libraries(SDENV2_cube_wave
  		-lGL
  	)
  	target_link_libraries(SDENV2_framebuffer_game
  		-lGL
  	)
  	target_link_libraries(SDENV2_smart_rockets
  		-lGL
  	)
  	target_link_libraries(SDENV2_maze
  		-lGL
  	)
  	target_link_libraries(SDENV2_network_chatting
  		-lGL
  	)
  ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

ENDIF(BUILD_DEMO)
