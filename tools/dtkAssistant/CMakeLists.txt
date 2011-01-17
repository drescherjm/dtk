### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Wed Feb  3 17:00:27 2010 (+0100)
## Version: $Id$
## Last-Updated: Mon Apr 26 16:42:04 2010 (+0200)
##           By: Julien Wintz
##     Update #: 36
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkAssistant)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS_MOC
  dtkAssistantMainWindow.h)
  
set(${PROJECT_NAME}_HEADERS
   ${${PROJECT_NAME}_HEADERS_MOC}
   )

set(${PROJECT_NAME}_SOURCES
  dtkAssistantMainWindow.cpp
  main.cpp)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_ui(${PROJECT_NAME}_SOURCES_UIC ${${PROJECT_NAME}_FORMS})
qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES_UIC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkGui
  dtkHelp)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC} ${${PROJECT_NAME}_SOURCES_UIC})

## #################################################################
## Bundle setup
## #################################################################

if(APPLE)
  set(MACOSX_BUNDLE_ICON_FILE ${PROJECT_NAME}.icns)
  set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${dtk_VERSION})
  set(MACOSX_BUNDLE_VERSION ${dtk_VERSION})
  set(MACOSX_BUNDLE_LONG_VERSION_STRING Version ${dtk_VERSION})
  set(${PROJECT_NAME}_RESOURCE_DIR ${EXECUTABLE_OUTPUT_PATH}/${PROJECT_NAME}.app/Contents/Resources)
  add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} ARGS -E make_directory ${${PROJECT_NAME}_RESOURCE_DIR}
    COMMAND ${CMAKE_COMMAND} ARGS -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.icns ${${PROJECT_NAME}_RESOURCE_DIR})
endif(APPLE)

## #################################################################
## Installation
## #################################################################

install(TARGETS ${PROJECT_NAME}
   BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin)

if(APPLE)
  install(CODE "execute_process(COMMAND macdeployqt \${CMAKE_INSTALL_PREFIX}/bin/${PROJECT_NAME}.app)")
endif(APPLE)
