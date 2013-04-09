### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:19:46 2013 (+0100)
## Version:
## Last-Updated: Tue Apr  9 13:14:38 2013 (+0200)
##           By: Thibaud Kloczko
##     Update #: 30
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
add_subdirectory(dtk3DQuick)
endif(Qt53D_FOUND)
