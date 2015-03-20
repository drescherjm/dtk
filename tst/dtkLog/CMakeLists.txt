## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

project(dtkLogTest)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS_MOC
  dtkLoggerHandlersTest.h)

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS_MOC})

set(${PROJECT_NAME}_SOURCES
  dtkLoggerHandlersTest.cpp)

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
target_link_libraries(${PROJECT_NAME} Qt5::Test)

target_link_libraries(${PROJECT_NAME} dtkLog)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkLoggerHandlersTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkLogTest dtkLoggerHandlersTest)

######################################################################
### CMakeLists.txt ends here
