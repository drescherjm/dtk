### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Sep  4 10:11:02 2009 (+0200)
## Version: $Id$
## Last-Updated: Mon Dec 13 13:50:54 2010 (+0100)
##           By: Thibaud Kloczko
##     Update #: 84
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkComposer)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkComposer.h
  dtkComposerEdge.h
  dtkComposerExport.h
  dtkComposerNode.h
  dtkComposerNodeData.h
  dtkComposerNodeFactory.h
  dtkComposerNodeFile.h
  dtkComposerNodeInteger.h
  dtkComposerNodeProcess.h
  dtkComposerNodeProperty.h
  dtkComposerNodeString.h
  dtkComposerNodeView.h
  dtkComposerReader.h
  dtkComposerScene.h
  dtkComposerView.h
  dtkComposerWriter.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkComposer.h
  dtkComposerEdge.h
  dtkComposerNode.h
  dtkComposerNodeData.h
  dtkComposerNodeFactory.h
  dtkComposerNodeFile.h
  dtkComposerNodeInteger.h
  dtkComposerNodeProcess.h
  dtkComposerNodeProperty.h
  dtkComposerNodeString.h
  dtkComposerNodeView.h
  dtkComposerReader.h
  dtkComposerScene.h
  dtkComposerView.h
  dtkComposerWriter.h)

set(${PROJECT_NAME}_SOURCES
  dtkComposer.cpp
  dtkComposerEdge.cpp
  dtkComposerNode.cpp
  dtkComposerNodeData.cpp
  dtkComposerNodeFactory.cpp
  dtkComposerNodeFile.cpp
  dtkComposerNodeInteger.cpp
  dtkComposerNodeString.cpp
  dtkComposerNodeProcess.cpp
  dtkComposerNodeProperty.cpp
  dtkComposerNodeView.cpp
  dtkComposerReader.cpp
  dtkComposerScene.cpp
  dtkComposerView.cpp
  dtkComposerWriter.cpp)

# Include header files for Visual Studio.
SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)

## #################################################################
## Build rules
## #################################################################

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  # Shouldn't the QT_USE_FILE set this appropriately?
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

add_definitions(-DQSTATEMACHINE_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_WRAP})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkGui)

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
