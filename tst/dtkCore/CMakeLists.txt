### CMakeLists.txt ---
## 
## Author: Thibaud Kloczko
## Created: Tue Jul 23 08:35:32 2013 (+0200)
##
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkCoreTest)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkArrayTest.h
  dtkIteratorTest.h)

if(DTK_HAVE_ZLIB)
  set(${PROJECT_NAME}_HEADERS
    ${${PROJECT_NAME}_HEADERS}
    dtkCompressIOTest.h)
endif(DTK_HAVE_ZLIB)


set(${PROJECT_NAME}_SOURCES
  dtkArrayTest.cpp
  dtkIteratorTest.cpp)

if(DTK_HAVE_ZLIB)
  set(${PROJECT_NAME}_SOURCES
    ${${PROJECT_NAME}_SOURCES}
    dtkCompressIOTest.cpp)
endif(DTK_HAVE_ZLIB)

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

target_link_libraries(${PROJECT_NAME} dtkCore)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkArrayTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkCoreTest dtkArrayTest)
add_test(dtkIteratorTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkCoreTest dtkIteratorTest)

if(DTK_HAVE_ZLIB)
  add_test(dtkCompressIOTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkCoreTest dtkCompressIOTest)
endif(DTK_HAVE_ZLIB)
