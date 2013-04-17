### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Wed Apr 17 10:54:40 2013 (+0200)
## Version: 
## Last-Updated: Wed Apr 17 11:42:11 2013 (+0200)
##           By: Julien Wintz
##     Update #: 11
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkComposerQuickTest)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_SOURCES
  dtkComposerQuickViewTest.cpp)

set(${PROJECT_NAME}_SOURCES_RCC
  dtkComposerQuickViewTest.qrc)

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
qt5_use_modules(${PROJECT_NAME} Widgets)
qt5_use_modules(${PROJECT_NAME} Xml)

target_link_libraries(${PROJECT_NAME} dtkComposerQuick)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkComposerQuickViewTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkComposerQuickTest dtkComposerQuickViewTest)
