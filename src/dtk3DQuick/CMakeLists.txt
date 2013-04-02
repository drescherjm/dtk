### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Mon Apr  1 21:44:51 2013 (+0200)
## Version: 
## Last-Updated: Tue Apr  2 16:55:45 2013 (+0200)
##           By: Julien Wintz
##     Update #: 13
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
  dtk3DQuickPlugin.h
  dtk3DQuickView.h)

set(${PROJECT_NAME}_SOURCES
  dtk3DQuickPlugin.cpp
  dtk3DQuickView.cpp)

## #################################################################
## Build rules
## #################################################################

add_definitions(-DQT_PLUGIN)

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

target_link_libraries(${PROJECT_NAME} dtk3D)

target_link_libraries(${PROJECT_NAME} "-framework OpenGL")

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
