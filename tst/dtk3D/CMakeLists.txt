### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Fri Mar 22 10:30:51 2013 (+0100)
## Version: 
## Last-Updated: Mon Apr  8 15:40:06 2013 (+0200)
##           By: Julien Wintz
##     Update #: 57
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
  dtk3DEffectTest.h
  dtk3DItemTest.h
  dtk3DMeshTest.h
  dtk3DShaderTest.h
  dtk3DViewTest.h)

set(${PROJECT_NAME}_SOURCES
  dtk3DEffectTest.cpp
  dtk3DItemTest.cpp
  dtk3DMeshTest.cpp
  dtk3DShaderTest.cpp
  dtk3DViewTest.cpp)

set(${PROJECT_NAME}_SOURCES_RCC
  dtk3DEffectTest.qrc
  dtk3DShaderTest.qrc)

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

qt5_use_modules(${PROJECT_NAME} 3D)
qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Test)
qt5_use_modules(${PROJECT_NAME} OpenGL)

target_link_libraries(${PROJECT_NAME} dtk3D)

## ###################################################################
## Test rules
## ###################################################################

add_test(dtk3DViewTest   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DTest dtk3DViewTest)
add_test(dtk3DItemTest   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DTest dtk3DItemTest)
add_test(dtk3DMeshTest   ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DTest dtk3DMeshTest)
add_test(dtk3DShaderTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DTest dtk3DShaderTest)
add_test(dtk3DEffectTest ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/dtk3DTest dtk3DEffecthTest)
