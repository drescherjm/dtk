### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Sep  4 10:11:02 2009 (+0200)
## Version: $Id$
## Last-Updated: Tue Mar  1 10:57:08 2011 (+0100)
##           By: Thibaud Kloczko
##     Update #: 115
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
  dtkComposerNodeBoolean.h
  dtkComposerNodeBooleanOperator.h
  dtkComposerNodeData.h
  dtkComposerNodeFactory.h
  dtkComposerNodeFile.h
  dtkComposerNodeNumber.h
  dtkComposerNodeNumberOperator.h
  dtkComposerNodeProcess.h
  dtkComposerNodeProperty.h
  dtkComposerNodeString.h
  dtkComposerNodeStringComparator.h
  dtkComposerNodeStringOperator.h
  dtkComposerNodeView.h
  dtkComposerNote.h
  dtkComposerReader.h
  dtkComposerScene.h
  dtkComposerView.h
  dtkComposerWriter.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkComposer.h
  dtkComposerEdge.h
  dtkComposerNode.h
  dtkComposerNodeBoolean.h
  dtkComposerNodeBooleanOperator.h
  dtkComposerNodeData.h
  dtkComposerNodeFactory.h
  dtkComposerNodeFile.h
  dtkComposerNodeNumber.h
  dtkComposerNodeNumberOperator.h
  dtkComposerNodeProcess.h
  dtkComposerNodeProperty.h
  dtkComposerNodeString.h
  dtkComposerNodeStringComparator.h
  dtkComposerNodeStringOperator.h
  dtkComposerNodeView.h
  dtkComposerNote.h
  dtkComposerReader.h
  dtkComposerScene.h
  dtkComposerView.h
  dtkComposerWriter.h)

set(${PROJECT_NAME}_SOURCES
  dtkComposer.cpp
  dtkComposerEdge.cpp
  dtkComposerNode.cpp
  dtkComposerNodeBoolean.cpp
  dtkComposerNodeBooleanOperator.cpp
  dtkComposerNodeData.cpp
  dtkComposerNodeFactory.cpp
  dtkComposerNodeFile.cpp
  dtkComposerNodeNumber.cpp
  dtkComposerNodeNumberOperator.cpp
  dtkComposerNodeProcess.cpp
  dtkComposerNodeProperty.cpp
  dtkComposerNodeString.cpp
  dtkComposerNodeStringComparator.cpp
  dtkComposerNodeStringOperator.cpp
  dtkComposerNodeView.cpp
  dtkComposerNote.cpp
  dtkComposerReader.cpp
  dtkComposerScene.cpp
  dtkComposerView.cpp
  dtkComposerWriter.cpp)

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
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## #################################################################
## Installation
## #################################################################

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
