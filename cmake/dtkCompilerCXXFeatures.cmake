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

## #################################################################
## Macros enabling some c+11 features whatever the compiler
## #################################################################

include(WriteCompilerDetectionHeader)

write_compiler_detection_header(
  FILE dtkCompilerCXXFeatures.h
  PREFIX DTK
  COMPILERS GNU Clang MSVC AppleClang
  FEATURES
  cxx_alignas
  cxx_alignof
  cxx_static_assert
  cxx_constexpr
  cxx_deleted_functions
  cxx_extern_templates
  cxx_final
  cxx_noexcept
  cxx_override
  cxx_nullptr
  cxx_attribute_deprecated
  VERSION 3.2
  )

## #################################################################
## Install rules
## #################################################################

install(FILES
  ${PROJECT_BINARY_DIR}/dtkCompilerCXXFeatures.h
  DESTINATION include/dtk
  )

######################################################################
### dtkCompilerHeader.cmake ends here
