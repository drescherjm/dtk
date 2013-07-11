### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Wed Apr 17 09:51:14 2013 (+0200)
## Version: 
## Last-Updated: Wed Apr 24 10:55:11 2013 (+0200)
##           By: Julien Wintz
##     Update #: 31
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkComposerQuick)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkComposerQuickPlugin.h)

set(${PROJECT_NAME}_SOURCES
  dtkComposerQuickPlugin.cpp)

## #################################################################
## Build rules
## #################################################################

add_definitions(-DQT_PLUGIN)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME} dtkComposer)

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Quick)
qt5_use_modules(${PROJECT_NAME} Widgets)
qt5_use_modules(${PROJECT_NAME} Xml)

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT ComposerQuick)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib
      COMPONENT ComposerQuick
         EXPORT dtkDepends)
