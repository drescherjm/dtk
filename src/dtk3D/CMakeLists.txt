### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Fri Mar 22 09:22:26 2013 (+0100)
## Version: 
## Last-Updated: Mon Apr  8 14:53:40 2013 (+0200)
##           By: Julien Wintz
##     Update #: 73
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
  dtk3D
  dtk3D.h
  dtk3DEffect
  dtk3DEffect.h
  dtk3DItem
  dtk3DItem.h
  dtk3DMesh
  dtk3DMesh.h
  dtk3DScene
  dtk3DScene.h
  dtk3DSettings
  dtk3DSettings.h
  dtk3DView
  dtk3DView.h)

set(${PROJECT_NAME}_SOURCES
  dtk3D.cpp
  dtk3DEffect.cpp
  dtk3DItem.cpp
  dtk3DMesh.cpp
  dtk3DScene.cpp
  dtk3DSettings.cpp
  dtk3DView.cpp)

set(${PROJECT_NAME}_SOURCES_RCC
  dtk3D.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_add_resources(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_SOURCES_RCC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} 3D)
qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} OpenGL)

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
