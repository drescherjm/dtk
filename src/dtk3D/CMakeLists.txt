### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Fri Mar 22 09:22:26 2013 (+0100)
## Version: 
## Last-Updated: Fri Mar 22 10:27:10 2013 (+0100)
##           By: Julien Wintz
##     Update #: 12
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtk3D)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtk3DView.h)

set(${PROJECT_NAME}_SOURCES
  dtk3DView.cpp)

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} 3D)
qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Widgets)

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT 3D)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib
      COMPONENT 3D
         EXPORT dtkDepends)

## ###################################################################
## Target export
## ###################################################################

list(APPEND DTK_TARGETS ${PROJECT_NAME})
