### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Fri Mar 22 10:30:51 2013 (+0100)
## Version: 
## Last-Updated: Mon Mar 25 12:59:46 2013 (+0100)
##           By: Julien Wintz
##     Update #: 25
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
  dtk3DMeshTest.h
  dtk3DViewTest.h)

set(${PROJECT_NAME}_SOURCES
  dtk3DMeshTest.cpp
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
add_test(dtk3DMeshTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DTest dtk3DMeshTest)
