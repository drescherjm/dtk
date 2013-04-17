### CMakeLists.txt ---
## 
## Author: Julien Wintz
## Created: Tue Apr  2 10:04:48 2013 (+0200)
## Version: 
## Last-Updated: Wed Apr 17 10:46:48 2013 (+0200)
##           By: Julien Wintz
##     Update #: 9
######################################################################
## 
### Change Log:
## 
######################################################################

add_subdirectory(dtk3DQuick)
add_subdirectory(dtkComposerQuick)

configure_file(dtk3DQuickConfig.h.in ${CMAKE_SOURCE_DIR}/src/dtk3DQuick/dtk3DQuickConfig)
configure_file(dtk3DQuickConfig.h.in ${CMAKE_SOURCE_DIR}/src/dtk3DQuick/dtk3DQuickConfig.h)

configure_file(dtkComposerQuickConfig.h.in ${CMAKE_SOURCE_DIR}/src/dtkComposerQuick/dtkComposerQuickConfig)
configure_file(dtkComposerQuickConfig.h.in ${CMAKE_SOURCE_DIR}/src/dtkComposerQuick/dtkComposerQuickConfig.h)
