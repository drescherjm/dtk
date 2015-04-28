### CMakeLists.txt ---
##
## Author: Julien Wintz
## Created: Mon Feb  4 12:20:18 2013 (+0100)
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtkDistributedCommunicator)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/customGraph.graph"  "${CMAKE_CURRENT_BINARY_DIR}" COPYONLY)
