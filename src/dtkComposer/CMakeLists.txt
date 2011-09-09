### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Fri Sep  4 10:11:02 2009 (+0200)
## Version: $Id$
## Last-Updated: Thu Sep  8 14:36:42 2011 (+0200)
##           By: Julien Wintz
##     Update #: 142
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
  dtkComposerNodeCase.h
  dtkComposerNodeConditional.h
  dtkComposerNodeControl.h
  dtkComposerNodeControlBlock.h
  dtkComposerNodeData.h
  dtkComposerNodeFactory.h
  dtkComposerNodeFile.h
  dtkComposerNodeLog.h
  dtkComposerNodeLoop.h
  dtkComposerNodeLoopFor.h
  dtkComposerNodeLoopWhile.h
  dtkComposerNodeNumber.h
  dtkComposerNodeNumberComparator.h
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
  dtkComposerNodeCase.h
  dtkComposerNodeConditional.h
  dtkComposerNodeControl.h
  dtkComposerNodeControlBlock.h
  dtkComposerNodeData.h
  dtkComposerNodeFactory.h
  dtkComposerNodeFile.h
  dtkComposerNodeLog.h
  dtkComposerNodeLoop.h
  dtkComposerNodeLoopFor.h
  dtkComposerNodeLoopWhile.h
  dtkComposerNodeNumber.h
  dtkComposerNodeNumberComparator.h
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
  dtkComposerNodeCase.cpp
  dtkComposerNodeConditional.cpp
  dtkComposerNodeControl.cpp
  dtkComposerNodeControlBlock.cpp
  dtkComposerNodeData.cpp
  dtkComposerNodeFactory.cpp
  dtkComposerNodeFile.cpp
  dtkComposerNodeLog.cpp
  dtkComposerNodeLoop.cpp
  dtkComposerNodeLoopFor.cpp
  dtkComposerNodeLoopWhile.cpp
  dtkComposerNodeNumber.cpp
  dtkComposerNodeNumberComparator.cpp
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
  add_definitions(-DQT_NO_DEBUG)
endif(NOT MSVC)

add_definitions(-DQSTATEMACHINE_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

if(DTK_USE_PRECOMPILED_HEADERS)
  add_precompiled_header(${PROJECT_NAME}_SOURCES_PCH 
    "dtkPch/dtkPch.h" "../dtkPch/dtkPch.cpp" 
    ${${PROJECT_NAME}_SOURCES}
    ${${PROJECT_NAME}_HEADERS}
    ${${PROJECT_NAME}_SOURCES_MOC}
    ${${PROJECT_NAME}_SOURCES_WRAP})
endif(DTK_USE_PRECOMPILED_HEADERS)

if(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_WRAP})

else(BUILD_SHARED_LIBS)

add_library(${PROJECT_NAME} STATIC
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES_PCH}
  ${${PROJECT_NAME}_SOURCES_WRAP})

endif(BUILD_SHARED_LIBS)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkMath
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

foreach(header ${${PROJECT_NAME}_HEADERS})
  string(REGEX REPLACE "(.*)\\.h\$" "\\1" h ${header})
  set(${PROJECT_NAME}_HEADERS_QTS "${${PROJECT_NAME}_HEADERS_QTS}" ${h})
endforeach(header)

install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
