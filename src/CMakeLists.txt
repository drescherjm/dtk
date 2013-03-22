### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:29:13 2013 (+0100)
## Version: 
## Last-Updated: Fri Mar 22 09:37:49 2013 (+0100)
##           By: Julien Wintz
##     Update #: 29
######################################################################
## 
### Change Log:
## 
######################################################################

set(DTK_TARGETS)

add_subdirectory(dtk)
add_subdirectory(dtkLog)
add_subdirectory(dtkTest)
add_subdirectory(dtkCore)
add_subdirectory(dtkDistributed)
if(Qt53D_FOUND)
add_subdirectory(dtk3D)
endif(Qt53D_FOUND)

export(TARGETS ${DTK_TARGETS} FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake") # dtkLog dtkCore dtkDistributed
