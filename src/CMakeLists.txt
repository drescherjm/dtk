### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:29:13 2013 (+0100)
## Version: 
## Last-Updated: Wed Mar 20 12:37:00 2013 (+0100)
##           By: Julien Wintz
##     Update #: 13
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtk)
add_subdirectory(dtkLog)
add_subdirectory(dtkCore)
add_subdirectory(dtkDistributed)
add_subdirectory(dtkComposer)
add_subdirectory(dtkTest)

export(TARGETS dtkLog dtkCore dtkDistributed dtkComposer FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake")
