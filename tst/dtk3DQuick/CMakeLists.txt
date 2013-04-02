### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Mon Apr  1 22:48:59 2013 (+0200)
## Version: 
## Last-Updated: Mon Apr  1 23:26:34 2013 (+0200)
##           By: Julien Wintz
##     Update #: 18
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtk3DQuickTest)

## ###################################################################
## Setup
## ###################################################################

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/dtk3DQuickTest.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/dtk3DQuickTest.h")

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_SOURCES
  dtk3DQuickTest.cpp)

## ###################################################################
## Input - introspected
## ###################################################################

# create_test_sourcelist(
#     ${PROJECT_NAME}_SOURCES_TST
#     ${PROJECT_NAME}.cpp
#   ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Build rules
## ###################################################################

add_executable(${PROJECT_NAME}
#  ${${PROJECT_NAME}_SOURCES_TST}
  ${${PROJECT_NAME}_SOURCES})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} QuickTest)

target_link_libraries(${PROJECT_NAME} dtk3DQuick)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtk3DQuickTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DQuickTest -input ${CMAKE_CURRENT_SOURCE_DIR})
