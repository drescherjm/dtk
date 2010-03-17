### CMakeLists.txt --- 
## 
## Author: Julien Wintz
## Copyright (C) 2008 - Julien Wintz, Inria.
## Created: Tue Mar 16 11:01:20 2010 (+0100)
## Version: $Id$
## Last-Updated: Wed Mar 17 08:50:25 2010 (+0100)
##           By: Julien Wintz
##     Update #: 47
######################################################################
## 
### Commentary: 
## 
######################################################################
## 
### Change log:
## 
######################################################################

project(dtkSsh)

## #################################################################
## Sources
## #################################################################

set(${PROJECT_NAME}_HEADERS
  dtkSshCallbacks.h
  dtkSshLibssh.h
  dtkSshSsh2.h
)

set(${PROJECT_NAME}_HEADERS_MOC
  dtkSshController.h
)

set(${PROJECT_NAME}_SOURCES
  dtkSshAgent.c
  dtkSshAuth.c
  dtkSshBase64.c
  dtkSshBuffer.c
  dtkSshCallbacks.c
  dtkSshChannels.c
  dtkSshClient.c
  dtkSshConfig.c
  dtkSshConnect.c
  dtkSshController.cpp
  dtkSshCrc32.c
  dtkSshCrypt.c
  dtkSshDh.c
  dtkSshError.c
  dtkSshGcrypt_missing.c
  dtkSshGzip.c
  dtkSshInit.c
  dtkSshKex.c
  dtkSshKeyfiles.c
  dtkSshKeys.c
  dtkSshLog.c
  dtkSshMatch.c
  dtkSshMessages.c
  dtkSshMisc.c
  dtkSshOptions.c
  dtkSshPacket.c
  dtkSshPoll.c
  dtkSshSession.c
  dtkSshScp.c
  dtkSshSocket.c
  dtkSshString.c
  dtkSshWrapper.c
)

## #################################################################
## Build rules
## #################################################################

if (OPENSSL_FOUND)
  set(HAVE_LIBCRYPTO 1)
endif (OPENSSL_FOUND)

if (Z_LIBRARY)
  set(HAVE_LIBZ 1)
endif (Z_LIBRARY)

include(dtkSshConfigureChecks.cmake)

configure_file(dtkSshConfig.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/dtkSshConfig.h)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_definitions(${QT_DEFINITIONS})
add_definitions(-DQT_SHARED)
add_definitions(-DQT_NO_DEBUG)

qt4_wrap_cpp(${PROJECT_NAME}_SOURCES_MOC ${${PROJECT_NAME}_HEADERS_MOC})

add_library(${PROJECT_NAME} SHARED
  ${${PROJECT_NAME}_SOURCES}
  ${${PROJECT_NAME}_SOURCES_MOC}
)

target_link_libraries(${PROJECT_NAME}
  ${QT_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  dtkCore
)
