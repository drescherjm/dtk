### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:20:18 2013 (+0100)
## Version: 
## Last-Updated: Mon Feb  4 12:29:14 2013 (+0100)
##           By: Julien Wintz
##     Update #: 5
######################################################################
## 
### Change Log:
## 
######################################################################

project(dtkDistributedTest)

## ###################################################################
## Input
## ###################################################################

set(${PROJECT_NAME}_HEADERS)

set(${PROJECT_NAME}_SOURCES)
# e.g. dtkDistributedCommunicatorTest

## ###################################################################
## Build rules
## ###################################################################

add_executable(${PROJECT_NAME}
  ${PROJECT_NAME}_HEADERS
  ${PROJECT_NAME}_SROUCES)

## ###################################################################
## Link rules
## ###################################################################

qt5_use_modules(${PROJECT_NAME} Core)
qt5_use_modules(${PROJECT_NAME} Test)

target_link_libraries(${PROJECT_NAME} dtkDistributed)

## ###################################################################
## CTest rules
## ###################################################################

# e.g. add_test(NAME dtkDistributedCommunicatorTest COMMAND dtkDistributedTest dtkDistributedCommunicatorTest)
