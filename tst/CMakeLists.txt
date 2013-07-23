### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 12:19:46 2013 (+0100)
## Version:
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtkLog)
add_subdirectory(dtkComposer)
add_subdirectory(dtkMath)
add_subdirectory(dtkWidgets)

if(Qt53D_FOUND)
add_subdirectory(dtk3D)
add_subdirectory(dtk3DQuick)
endif(Qt53D_FOUND)
