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

project(dtkMetaTest)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS_MOC
  dtkMetaTypeTest.h
  dtkMetaContainerSequentialTest.h
  dtkMetaContainerSequentialTest.tpp)

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS_MOC})

set(${PROJECT_NAME}_SOURCES
  dtkMetaTypeTest.cpp
  dtkMetaContainerSequentialTest.cpp)

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

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Test)

target_link_libraries(${PROJECT_NAME} dtkMeta dtkCore)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkMetaTypeTest                ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkMetaTest dtkMetaTypeTest)
add_test(dtkMetaContainerSequentialTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkMetaTest dtkMetaContainerSequentialTest)

######################################################################
### CMakeLists.txt ends here
