### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Mon Apr 15 12:06:16 2013 (+0200)
## Version: 
## Last-Updated: Mon Apr 15 12:12:15 2013 (+0200)
##           By: Julien Wintz
##     Update #: 18
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkWidgetsTest)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkWidgetsTagCloudTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkWidgetsTagCloudTest.cpp)

## ###################################################################
## Input - introspected
## ###################################################################

create_test_sourcelist(
    ${PROJECT_NAME}_SOURCES_TST
    ${PROJECT_NAME}.cpp
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Build rules
## ###################################################################

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES_TST}
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Test)
qt5_use_modules(${PROJECT_NAME} Widgets)

target_link_libraries(${PROJECT_NAME} dtkWidgets)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkWidgetsTagCloudTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkWidgetsTest dtkWidgetsTagCloudTest)
