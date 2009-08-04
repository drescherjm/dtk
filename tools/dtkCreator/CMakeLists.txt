### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Aug  3 17:34:51 2009 (+0200)
## Version: $Id$
## Last-Updated: Tue Aug  4 10:30:11 2009 (+0200)
##           By: Julien Wintz
##     Update #: 9
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

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_SOURCES_MOC}
  ${${PROJECT_NAME}_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  dtkCore
  dtkScript
  dtkGui
)
