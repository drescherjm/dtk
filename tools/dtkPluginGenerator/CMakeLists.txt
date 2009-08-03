### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Mon Mar  9 21:07:07 2009 (+0100)
## Version: $Id$
## Last-Updated: Mon Jul 20 22:33:18 2009 (+0200)
##           By: Julien Wintz
##     Update #: 25
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkPluginGenerator)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkPluginGeneratorMainWindow.h
)

set(${PROJECT_NAME}_SOURCES
  dtkPluginGenerator.cpp
  dtkPluginGeneratorCMakeLists.cpp
  dtkPluginGeneratorTypeHeaderFile.cpp
  dtkPluginGeneratorTypeSourceFile.cpp
  dtkPluginGeneratorPluginHeaderFile.cpp
  dtkPluginGeneratorPluginSourceFile.cpp
  dtkPluginGeneratorLoaderHeaderFile.cpp
  dtkPluginGeneratorLoaderSourceFile.cpp
  dtkPluginGeneratorExportHeaderFile.cpp
  dtkPluginGeneratorMainWindow.cpp
  anyoption.cpp
  main.cpp
)

set(${PROJECT_NAME}_FORMS
  dtkPluginGeneratorMainWindow.ui
)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_ui(${PROJECT_NAME}_HEADERS_UIC ${${PROJECT_NAME}_FORMS})

qt4_wrap_cpp(${PROJECT_NAME}_HEADERS_MOC ${${PROJECT_NAME}_HEADERS})

add_executable(${PROJECT_NAME} MACOSX_BUNDLE
  ${${PROJECT_NAME}_HEADERS_UIC}
  ${${PROJECT_NAME}_HEADERS_MOC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
)
