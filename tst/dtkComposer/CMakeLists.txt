### CMakeLists.txt ---
##
## Author: Thibaud Kloczko
## Created: Mon Mar 25 11:03:20 2013 (+0100)
## Version:
## Last-Updated: Mon Apr 15 11:20:24 2013 (+0200)
##           By: Julien Wintz
##     Update #: 24
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
  dtkComposerNodeTest.h
  dtkComposerSceneTest.h
  dtkComposerTransmitterTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkComposerNodeTest.cpp
  dtkComposerSceneTest.cpp
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

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Test)
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} Qt5::Xml)

target_link_libraries(${PROJECT_NAME} dtkComposer)
target_link_libraries(${PROJECT_NAME} dtkLog)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkComposerNodeTest        ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkComposerTest dtkComposerNodeTest)
add_test(dtkComposerTransmitterTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkComposerTest dtkComposerTransmitterTest)
