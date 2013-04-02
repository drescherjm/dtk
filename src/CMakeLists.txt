### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:29:13 2013 (+0100)
## Version: 
## Last-Updated: Mon Apr  1 21:49:27 2013 (+0200)
##           By: Julien Wintz
##     Update #: 51
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtk)
add_subdirectory(dtkLog)
add_subdirectory(dtkTest)
add_subdirectory(dtkCore)
add_subdirectory(dtkDistributed)

if(Qt53D_FOUND)
add_subdirectory(dtk3D)
add_subdirectory(dtk3DQuick)
endif(Qt53D_FOUND)

set(DTK_TARGETS)
set(DTK_TARGETS ${DTK_TARGETS} dtkLog)
set(DTK_TARGETS ${DTK_TARGETS} dtkCore)
set(DTK_TARGETS ${DTK_TARGETS} dtkDistributed)

if(Qt53D_FOUND)
set(DTK_TARGETS ${DTK_TARGETS} dtk3D)
set(DTK_TARGETS ${DTK_TARGETS} dtk3DQuick)
endif(Qt53D_FOUND)

export(TARGETS ${DTK_TARGETS} FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake")
