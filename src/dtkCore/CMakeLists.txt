### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Jul 20 18:39:20 2009 (+0200)
## Version: $Id$
## Last-Updated: Tue May 15 13:35:15 2012 (+0200)
##           By: Julien Wintz
##     Update #: 291
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkCore)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkAbstractContainer.h
  dtkAbstractData.h
  dtkAbstractDataFactory.h
  dtkAbstractDataReader.h
  dtkAbstractDataDeserializer.h
  dtkAbstractDataSerializer.h
  dtkAbstractDataWriter.h
  dtkAbstractDataComposite.h
  dtkAbstractDataComposite.tpp
  dtkAbstractDataConverter.h
  dtkAbstractFactory.h
  dtkAbstractObject.h
  dtkAbstractProcess.h
  dtkAbstractProcessFactory.h
  dtkAbstractView.h
  dtkAbstractViewAnimator.h
  dtkAbstractViewFactory.h
  dtkAbstractViewInteractor.h
  dtkAbstractViewNavigator.h
  dtkContainerList.h
  dtkContainerList.tpp
  dtkContainerVector.h
  dtkContainerVector.tpp
  dtkCpuid.h
  dtkGlobal.h
  dtkPlugin.h
  dtkPluginManager.h
  dtkUpdater.h
  dtkSignalBlocker.h
  dtkSingleton.h
  dtkSingletonDeclare.h
  dtkSmartPointer.h)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAbstractContainer.h
  dtkAbstractData.h
  dtkAbstractDataFactory.h
  dtkAbstractDataReader.h
  dtkAbstractDataSerializer.h
  dtkAbstractDataDeserializer.h
  dtkAbstractDataWriter.h
  dtkAbstractDataComposite.h
  dtkAbstractDataConverter.h
  dtkAbstractFactory.h
  dtkAbstractObject.h
  dtkAbstractProcess.h
  dtkAbstractProcessFactory.h
  dtkAbstractView.h
  dtkAbstractViewAnimator.h
  dtkAbstractViewFactory.h
  dtkAbstractViewInteractor.h
  dtkAbstractViewNavigator.h
  dtkPlugin.h
  dtkPluginManager.h
  dtkUpdater_p.h)

set(${PROJECT_NAME}_SOURCES
  dtkAbstractContainer.cpp
  dtkAbstractDataFactory.cpp
  dtkAbstractData.cpp
  dtkAbstractDataReader.cpp
  dtkAbstractDataSerializer.cpp
  dtkAbstractDataDeserializer.cpp
  dtkAbstractDataWriter.cpp
  dtkAbstractDataComposite.cpp
  dtkAbstractDataConverter.cpp
  dtkAbstractFactory.cpp
  dtkAbstractObject.cpp
  dtkAbstractProcessFactory.cpp
  dtkAbstractProcess.cpp
  dtkAbstractViewFactory.cpp
  dtkAbstractView.cpp
  dtkAbstractViewAnimator.cpp
  dtkAbstractViewInteractor.cpp
  dtkAbstractViewNavigator.cpp
  dtkCpuid.cpp
  dtkPlugin.cpp
  dtkPluginManager.cpp
  dtkSignalBlocker.h
  dtkSingleton.cpp
  dtkSingletonDeclare.cpp
  dtkSmartPointer.cpp
  dtkUpdater.cpp)

## #################################################################
## Wrapping
## #################################################################

set(${PROJECT_NAME}_SOURCES_WRAP)

if(DTK_BUILD_WRAPPERS AND SWIG_FOUND)

  set(${PROJECT_NAME}_WRAP_DEPENDS ${${PROJECT_NAME}_HEADERS})
  
  if(PYTHONLIBS_FOUND)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP core python ${PROJECT_SOURCE_DIR}/dtkCore.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif()
  
  if(TCL_FOUND)
    dtk_wrap(${PROJECT_NAME} ${PROJECT_NAME}_SOURCES_WRAP core tcl    ${PROJECT_SOURCE_DIR}/dtkCore.i ${${PROJECT_NAME}_WRAP_DEPENDS})
  endif()
  
endif()

## #################################################################
## Configure file
## #################################################################

configure_file (
  "${PROJECT_SOURCE_DIR}/dtkConfig.h.in"
  "${PROJECT_BINARY_DIR}/../../dtkConfig.h")

## #################################################################
## Build rules
## #################################################################

if(NOT MSVC)
add_definitions(-Wno-write-strings)
endif()

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
if(NOT MSVC)
  add_definitions(-DQT_NO_DEBUG)
endif()

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
  dtkLog)

if(TCL_FOUND)
  target_link_libraries(${PROJECT_NAME} ${TCL_LIBRARY})
endif()

if(PYTHONLIBS_FOUND)
  target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
endif()

## #################################################################
## Export header file
## #################################################################

add_compiler_export_flags()

generate_export_header(${PROJECT_NAME}
  EXPORT_FILE_NAME "${PROJECT_NAME}Export.h")

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
  COMMAND ${CMAKE_COMMAND} ARGS -E copy "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}"
  COMMAND ${CMAKE_COMMAND} ARGS -E copy "${${PROJECT_NAME}_BINARY_DIR}/${PROJECT_NAME}Export.h" "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export")

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS}
 "${CMAKE_BINARY_DIR}/${PROJECT_NAME}Export.h")

## #################################################################
## Handling of generated script modules
## #################################################################

set(${PROJECT_NAME}_MODULES)

if(DTK_BUILD_WRAPPERS AND SWIG_FOUND AND PYTHONLIBS_FOUND)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  DEPENDS ${PROJECT_SOURCE_DIR}/dtkCore.i
  COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${CMAKE_BINARY_DIR}/modules
  COMMAND ${CMAKE_COMMAND} ARGS -E copy ${${PROJECT_NAME}_BINARY_DIR}/core.py ${CMAKE_BINARY_DIR}/modules
  COMMENT "-- Moving python modules to ${CMAKE_BINARY_DIR}/modules")

set(${PROJECT_NAME}_MODULES ${CMAKE_BINARY_DIR}/modules/core.py)

endif()

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

install(FILES ${dtk_BINARY_DIR}/dtkConfig.h DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_HEADERS_QTS} DESTINATION include/${PROJECT_NAME})
install(FILES ${${PROJECT_NAME}_MODULES} DESTINATION modules)
install(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib)
