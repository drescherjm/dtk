### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Fri Mar 22 10:30:51 2013 (+0100)
## Version: 
## Last-Updated: Fri Mar 22 14:40:45 2013 (+0100)
##           By: Julien Wintz
##     Update #: 22
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtk3DTest)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS
  dtk3DViewTest.h)

set(${PROJECT_NAME}_SOURCES
  dtk3DViewTest.cpp)

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
qt5_use_modules(${PROJECT_NAME} 3D)

target_link_libraries(${PROJECT_NAME} dtk3D)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtk3DViewTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DTest dtk3DViewTest)
