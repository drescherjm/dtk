### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:20:18 2013 (+0100)
## Version: 
## Last-Updated: Mon Feb  4 15:47:30 2013 (+0100)
##           By: Julien Wintz
##     Update #: 39
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
  dtkDistributedCommunicatorTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedCommunicatorTest.cpp)

## ###################################################################
## 
## ###################################################################

create_test_sourcelist(
    ${PROJECT_NAME}_SOURCES_TST
    ${PROJECT_NAME}.cpp
  ${${PROJECT_NAME}_SOURCES})

message(${${PROJECT_NAME}_SOURCES_TST})
message(${${PROJECT_NAME}_SOURCES})

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

add_test(dtkDistributedCommunicatorTest dtkDistributedTest dtkDistributedCommunicatorTest)
