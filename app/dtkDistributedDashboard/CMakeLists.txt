### CMakeLists.txt ---
##
## Author: Nicolas Niclausse
## Copyright (C) 2012 - Nicolas Niclausse, Inria.
######################################################################

project(dtkDistributedDashboard)

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
  dtkDistributed
  dtkLog
 )

target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_link_libraries(${PROJECT_NAME} Qt5::Network)
target_link_libraries(${PROJECT_NAME} Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Quick)

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
