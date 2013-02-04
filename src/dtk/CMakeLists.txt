### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Created: Mon Feb  4 10:45:58 2013 (+0100)
## Version: 
## Last-Updated: Mon Feb  4 16:40:46 2013 (+0100)
##           By: Julien Wintz
##     Update #: 10
######################################################################
## 
### Change Log:
## 
######################################################################

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/dtkConfig.h.in"
  "${CMAKE_CURRENT_SOURCE_DIR}/dtkConfig.h")

## ###################################################################
## Install rules
## ###################################################################

install(FILES dtkConfig   DESTINATION include/dtk/)
install(FILES dtkConfig.h DESTINATION include/dtk/)
