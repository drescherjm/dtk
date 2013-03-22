### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:19:46 2013 (+0100)
## Version: 
## Last-Updated: Fri Mar 22 14:10:55 2013 (+0100)
##           By: Julien Wintz
##     Update #: 24
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtkLog)
add_subdirectory(dtkDistributed)
if(Qt53D_FOUND)
add_subdirectory(dtk3D)
endif(Qt53D_FOUND)
