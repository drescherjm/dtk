### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Mon Apr 15 11:46:27 2013 (+0200)
## Version: 
## Last-Updated: Mon Apr 15 15:42:28 2013 (+0200)
##           By: Julien Wintz
##     Update #: 57
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkWidgets)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkWidgetsTag.h
  dtkWidgetsTagCloud.h
  dtkWidgetsTagCloudController.h
  dtkWidgetsTagCloudDesc.h
  dtkWidgetsTagCloudItem.h
  dtkWidgetsTagCloudLayout.h
  dtkWidgetsTagCloudList.h
  dtkWidgetsTagCloudScope.h
  dtkWidgetsTagCloudScopeItem.h
  dtkWidgetsTagCloudView.h)

set(${PROJECT_NAME}_SOURCES
  dtkWidgetsTag.cpp
  dtkWidgetsTagCloud.cpp
  dtkWidgetsTagCloudController.cpp
  dtkWidgetsTagCloudDesc.cpp
  dtkWidgetsTagCloudItem.cpp
  dtkWidgetsTagCloudLayout.cpp
  dtkWidgetsTagCloudList.cpp
  dtkWidgetsTagCloudScope.cpp
  dtkWidgetsTagCloudScopeItem.cpp
  dtkWidgetsTagCloudView.cpp)

set(${PROJECT_NAME}_SOURCES_RCC
  dtkWidgetsTagCloud.qrc)

## #################################################################
## Build rules
## #################################################################

qt5_add_resources(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_SOURCES_RCC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

# target_link_libraries(${PROJECT_NAME} ...)

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Widgets)

## ###################################################################
## Install rules - files
## ###################################################################

install(FILES ${${PROJECT_NAME}_HEADERS}
  DESTINATION include/${PROJECT_NAME}
    COMPONENT widgets)

## ###################################################################
## Install rules - targets
## ###################################################################

install(TARGETS ${PROJECT_NAME}
    DESTINATION lib
      COMPONENT widgets
         EXPORT dtkDepends)
