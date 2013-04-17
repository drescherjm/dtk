### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:19:46 2013 (+0100)
## Version:
## Last-Updated: Wed Apr 17 10:56:45 2013 (+0200)
##           By: Julien Wintz
##     Update #: 34
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtkLog)
add_subdirectory(dtkComposer)
add_subdirectory(dtkComposerQuick)
add_subdirectory(dtkDistributed)
add_subdirectory(dtkWidgets)

if(Qt53D_FOUND)
add_subdirectory(dtk3D)
add_subdirectory(dtk3DQuick)
endif(Qt53D_FOUND)
