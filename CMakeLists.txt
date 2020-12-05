cmake_minimum_required(VERSION 3.17)
project(tp_wolfenstein)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
SET(CMAKE_CXX_FLAGS -pthread)

INCLUDE(FindPkgConfig)

PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
PKG_SEARCH_MODULE(SDL2IMAGE REQUIRED SDL2_image>=2.0.0)
pkg_check_modules(SDL2_Mixer REQUIRED IMPORTED_TARGET SDL2_mixer)

INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 11)

add_executable(tp_wolfenstein main.cpp Game/Map.cpp Game/Map.h Game/Player.cpp Game/Player.h Game/Positionable.cpp Game/Positionable.h Graphics/SdlWindow.cpp Graphics/SdlWindow.h Exceptions/SdlException.cpp Exceptions/SdlException.h Graphics/SdlTexture.cpp Graphics/SdlTexture.h Graphics/Area.cpp Graphics/Area.h Graphics/SdlSprite.cpp Graphics/SdlSprite.h Game/Game.cpp Game/Game.h Game/EventHandler.cpp Game/EventHandler.h Music/SdlAudioPlayer.cpp Music/SdlAudioPlayer.h Graphics/RayCaster.cpp Graphics/RayCaster.h Graphics/Sdl3DTexture.cpp Graphics/Sdl3DTexture.h Game/Wall_3d.cpp Game/Wall_3d.h Graphics/DrawingInfo.cpp Graphics/DrawingInfo.h Graphics/RayInfo.cpp Graphics/RayInfo.h Game/PositionableHandler.cpp Game/PositionableHandler.h Game/Enemy.cpp Game/Enemy.h Graphics/ObjectDrawer.cpp Graphics/ObjectDrawer.h)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES} PkgConfig::SDL2_Mixer)