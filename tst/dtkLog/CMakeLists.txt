### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb 11 20:47:00 2013 (+0100)
## Version: 
## Last-Updated: lun. févr.  3 16:21:41 2014 (+0100)
##           By: Thibaud Kloczko
##     Update #: 20
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkLogTest)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtkLoggerTest.h
  dtkLoggerEnvTest.h)

set(${PROJECT_NAME}_SOURCES
  dtkLoggerTest.cpp
  dtkLoggerEnvTest.cpp)

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

target_link_libraries(${PROJECT_NAME} dtkLog)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtkLoggerTest    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkLogTest dtkLoggerTest)
add_test(dtkLoggerEnvTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtkLogTest dtkLoggerEnvTest)