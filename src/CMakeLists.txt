### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:29:13 2013 (+0100)
## Version: 
## Last-Updated: Tue Feb 26 14:58:29 2013 (+0100)
##           By: Julien Wintz
##     Update #: 10
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtk)
add_subdirectory(dtkLog)
add_subdirectory(dtkCore)
add_subdirectory(dtkDistributed)
add_subdirectory(dtkTest)

export(TARGETS dtkLog dtkCore dtkDistributed APPEND FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake")
