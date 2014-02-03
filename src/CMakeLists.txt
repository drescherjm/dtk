### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:29:13 2013 (+0100)
## Version: 
## Last-Updated: lun. févr.  3 11:09:50 2014 (+0100)
##           By: Thibaud Kloczko
##     Update #: 85
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtk)
add_subdirectory(dtkCore)
add_subdirectory(dtkDistributed)
add_subdirectory(dtkMath)
add_subdirectory(dtkTest)
add_subdirectory(dtkWidgets)

set(DTK_TARGETS)
set(DTK_TARGETS ${DTK_TARGETS} dtkCore)
set(DTK_TARGETS ${DTK_TARGETS} dtkDistributed)
set(DTK_TARGETS ${DTK_TARGETS} dtkMath)
set(DTK_TARGETS ${DTK_TARGETS} dtkWidgets)

export(TARGETS ${DTK_TARGETS} FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake")
