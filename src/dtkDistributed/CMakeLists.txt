### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:16:39 2013 (+0100)
## Version: 
## Last-Updated: Mon Feb  4 12:22:49 2013 (+0100)
##           By: Julien Wintz
##     Update #: 12
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkDistributed)

## #################################################################
## Input
## #################################################################

set(${PROJECT_NAME}_HEADERS)

set(${PROJECT_NAME}_SOURCES)

## #################################################################
## Build rules
## #################################################################

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_HEADERS})

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Network)
