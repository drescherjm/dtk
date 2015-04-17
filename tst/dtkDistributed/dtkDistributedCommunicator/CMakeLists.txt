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

project(dtkCommunicatorTest)

## ###################################################################
## Build tree setup
## ###################################################################

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkDistributedArrayTest.h
  dtkDistributedBufferManagerTest.h
  dtkDistributedCommunicatorTest.h
  dtkDistributedContainerTest.h
  dtkDistributedGraphTopologyTest.h
  dtkDistributedSendRecvTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkDistributedArrayTest.cpp
  dtkDistributedBufferManagerTest.cpp
  dtkDistributedCommunicatorTest.cpp
  dtkDistributedContainerTest.cpp
  dtkDistributedGraphTopologyTest.cpp
  dtkDistributedSendRecvTest.cpp)

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

target_link_libraries(${PROJECT_NAME}
  dtkDistributed
  dtkLog)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkDistributedArrayTest         ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkDistributedArrayTest)
add_test(dtkDistributedBufferManagerTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkDistributedBufferManagerTest)
add_test(dtkDistributedCommunicatorTest  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkDistributedCommunicatorTest)
add_test(dtkDistributedContainerTest     ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkDistributedContainerTest)
add_test(dtkDistributedGraphTopologyTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkDistributedGraphTopologyTest)
add_test(dtkDistributedSendRecvTest      ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME} dtkDistributedSendRecvTest)

######################################################################
### CMakeLists.txt ends here
