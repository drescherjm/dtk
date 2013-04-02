### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Tue Apr  2 10:04:48 2013 (+0200)
## Version: 
## Last-Updated: Tue Apr  2 10:08:49 2013 (+0200)
##           By: Julien Wintz
##     Update #: 7
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtk3DQuick)

configure_file(dtk3DQuickConfig.h.in ${CMAKE_SOURCE_DIR}/src/dtk3DQuick/dtk3DQuickConfig)
configure_file(dtk3DQuickConfig.h.in ${CMAKE_SOURCE_DIR}/src/dtk3DQuick/dtk3DQuickConfig.h)
