## Version: $Id$
##
######################################################################
##
### Commentary:
##
######################################################################
##
### Change Log:
##
######################################################################
##
### Code:

configure_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/dtkConfig.h.in"
  "${PROJECT_BINARY_DIR}/dtkConfig.h")

## ###################################################################
## Install rules
## ###################################################################

install(FILES dtkConfig
  DESTINATION include/dtk/)

install(FILES "${PROJECT_BINARY_DIR}/dtkConfig.h"
  DESTINATION include/dtk/)

######################################################################
### CMakeLists.txt ends here
