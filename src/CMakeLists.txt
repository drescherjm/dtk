### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:29:13 2013 (+0100)
## Version: 
## Last-Updated: 2013 Wed Feb 27 16:41:15 (+0100)
##           By: Thibaud Kloczko
##     Update #: 11
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

export(TARGETS dtkLog dtkCore dtkDistributed FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake")
