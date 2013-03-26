### CMakeLists.txt ---
## 
## Author: Thibaud Kloczko
## Created: Mon Mar 25 11:03:20 2013 (+0100)
## Version: 
## Last-Updated: Mon Mar 25 12:17:58 2013 (+0100)
##           By: Thibaud Kloczko
##     Update #: 14
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkComposerTest)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkComposerTransmitterTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkComposerTransmitterTest.cpp)

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
qt5_use_modules(${PROJECT_NAME} Test)
qt5_use_modules(${PROJECT_NAME} Xml)
qt5_use_modules(${PROJECT_NAME} Gui)
qt5_use_modules(${PROJECT_NAME} Widgets)

target_link_libraries(${PROJECT_NAME} dtkComposer)
target_link_libraries(${PROJECT_NAME} dtkLog)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkComposerTransmitterTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkComposerTest dtkComposerTransmitterTest)
