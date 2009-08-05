### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Aug  3 17:34:51 2009 (+0200)
## Version: $Id$
## Last-Updated: Wed Aug  5 13:04:09 2009 (+0200)
##           By: Julien Wintz
##     Update #: 17
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkCreator)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS

)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkCreatorMainWindow.h
  dtkCreatorPluginBrowser.h
  dtkCreatorScriptBrowser.h
)

set(${PROJECT_NAME}_SOURCES
  dtkCreatorMainWindow.cpp
  dtkCreatorPluginBrowser.cpp
  dtkCreatorScriptBrowser.cpp
  main.cpp
)

set(${PROJECT_NAME}_RESOURCES
  icons/icons.qrc
)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

qt4_add_RESOURCES(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_RESOURCES})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript
  dtkGui
)
