### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Mon Apr  1 22:48:59 2013 (+0200)
## Version: 
## Last-Updated: Mon Apr  8 15:03:04 2013 (+0200)
##           By: Julien Wintz
##     Update #: 40
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtk3DQuickTest)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_SOURCES
  dtk3DQuickViewTest.cpp)

set(${PROJECT_NAME}_SOURCES_RCC
  dtk3DQuickViewTest.qrc)

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

qt5_add_resources(${PROJECT_NAME}_SOURCES_QRC ${${PROJECT_NAME}_SOURCES_RCC})

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES_QRC}
  ${${PROJECT_NAME}_SOURCES_TST}
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Quick)
qt5_use_modules(${PROJECT_NAME} Test)
qt5_use_modules(${PROJECT_NAME} OpenGL)

target_link_libraries(${PROJECT_NAME} dtk3DQuick)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtk3DQuickViewTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DQuickTest dtk3DQuickViewTest)
