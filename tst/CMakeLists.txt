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

if(DTK_BUILD_COMPOSER)
  add_subdirectory(dtkComposer)
endif(DTK_BUILD_COMPOSER)

add_subdirectory(dtkCore)

if(DTK_BUILD_DISTRIBUTED)
add_subdirectory(dtkDistributed)
endif(DTK_BUILD_DISTRIBUTED)

add_subdirectory(dtkLog)
add_subdirectory(dtkMeta)
add_subdirectory(dtkMath)

######################################################################
### CMakeLists.txt ends here
