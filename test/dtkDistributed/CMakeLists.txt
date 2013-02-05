### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:20:18 2013 (+0100)
## Version: 
## Last-Updated: Mon Feb  4 16:55:07 2013 (+0100)
##           By: Julien Wintz
##     Update #: 47
## Last-Updated: 2013 Mon Feb  4 15:39:14 (+0100)
##           By: Thibaud Kloczko
##     Update #: 17
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkDistributedTest)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDistributedCommunicatorTest.h
  dtkDistributedContainerTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedCommunicatorTest.cpp
  dtkDistributedContainerTest.cpp)

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

target_link_libraries(${PROJECT_NAME} dtkDistributed)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkDistributedCommunicatorTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkDistributedTest dtkDistributedCommunicatorTest)
add_test(dtkDistributedContainerTest    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkDistributedTest dtkDistributedContainerTest)
