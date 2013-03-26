### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:19:46 2013 (+0100)
## Version: 
## Last-Updated: Mon Mar 25 11:49:37 2013 (+0100)
##           By: Thibaud Kloczko
##     Update #: 26
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtkLog)
add_subdirectory(dtkDistributed)
add_subdirectory(dtkComposer)
if(Qt53D_FOUND)
add_subdirectory(dtk3D)
endif(Qt53D_FOUND)
