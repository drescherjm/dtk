### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Tue Mar 12 15:01:41 2013 (+0100)
## Version: 
## Last-Updated: Tue Mar 12 15:01:42 2013 (+0100)
##           By: Julien Wintz
##     Update #: 1
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkZipTest)

## ###################################################################

if(ZLIB_FOUND)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS_MOC
  dtkZipTest.h)

set(${PROJECT_NAME}_HEADERS
  ${${PROJECT_NAME}_HEADERS_MOC})

set(${PROJECT_NAME}_SOURCES
  dtkZipTest.cpp)

## #################################################################
## Build rules
## #################################################################

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

set(${PROJECT_NAME}_MAIN_SOURCES
    dtkZipTest.cpp)

create_test_sourcelist(${PROJECT_NAME}_SOURCES_TEST ${PROJECT_NAME}.cxx
  ${${PROJECT_NAME}_MAIN_SOURCES})

add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES_TEST}
  ${${PROJECT_NAME}_SOURCES_MOC} 
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

target_link_libraries(${PROJECT_NAME}
  ${QT_QTTEST_LIBRARY}
  ${QT_LIBRARIES}
  dtkLog
  dtkZip)

set_target_properties(${PROJECT_NAME} PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY "${EXECUTABLE_OUTPUT_PATH}")

foreach (test ${${PROJECT_NAME}_MAIN_SOURCES})
  get_filename_component(TName ${test} NAME_WE)
  add_test(NAME ${TName} COMMAND $<TARGET_FILE:${PROJECT_NAME}> ${TName})
endforeach()

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)
SOURCE_GROUP("Generated Files" FILES ${${PROJECT_NAME}_SOURCES_MOC})

## ###################################################################

endif(ZLIB_FOUND)

## ###################################################################
