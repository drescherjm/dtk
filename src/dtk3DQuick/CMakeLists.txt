### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Mon Apr  1 21:44:51 2013 (+0200)
## Version: 
## Last-Updated: Fri Apr  5 01:02:51 2013 (+0200)
##           By: Julien Wintz
##     Update #: 35
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtk3DQuick)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtk3DQuickItem.h
  dtk3DQuickPlugin.h
  dtk3DQuickScene.h
  dtk3DQuickView.h)

set(${PROJECT_NAME}_SOURCES
  dtk3DQuickItem.cpp
  dtk3DQuickPlugin.cpp
  dtk3DQuickScene.cpp
  dtk3DQuickView.cpp)

## #################################################################
## Build rules
## #################################################################

add_definitions(-DQT_PLUGIN)

include_directories(${OPENGL_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} 3D)
qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Quick)

target_link_libraries(${PROJECT_NAME} dtk3D ${OPENGL_LIBRARIES})

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT 3DQuick)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib
      COMPONENT 3DQuick
         EXPORT dtkDepends)
