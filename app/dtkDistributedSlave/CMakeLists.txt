### CMakeLists.txt ---
##
## Author: Nicolas Niclausse
## Copyright (C) 2012 - Nicolas Niclausse, Inria.
######################################################################

project(dtkDistributedSlave)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_SOURCES
  main.cpp)

## #################################################################
## Build rules
## #################################################################


add_executable(${PROJECT_NAME}
  ${${PROJECT_NAME}_SOURCES})

target_link_libraries(${PROJECT_NAME}
  dtkCore
  dtkDistributed
  dtkLog
 )

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Network)

## #################################################################
## Source file layout in development environments like Visual Studio
## #################################################################

SOURCE_GROUP("Header Files" REGULAR_EXPRESSION .*\\.h\$)

## #################################################################
## Installation
## #################################################################

install(TARGETS ${PROJECT_NAME}
   BUNDLE DESTINATION bin
  RUNTIME DESTINATION bin)
