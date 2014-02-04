### FindQwt.cmake --- 

# QWT_FOUND - system has Qwt
# QWT_INCLUDE_DIR - where to find qwt.h
# QWT_LIBRARIES - the libraries to link against to use Qwt
# QWT_LIBRARY - where to find the Qwt library (not for general use)

set(QWT_FOUND "NO")

find_path(QWT_INCLUDE_DIR 
  NAMES qwt.h
  PATHS $ENV{QWT_DIR}/src
  $ENV{QWT_DIR}/include
  ${QWT_DIR}/src
  ${QWT_DIR}/include
  ${QWT_DIR}/include/qwt
  /usr/local/qwt/include
  /usr/local/include
  /opt/qwt/include
  /usr/include/qwt
# /usr/include/qwt-qt4
  /usr/include)

#  set(QWT_NAMES ${QWT_NAMES} qwt qwt-qt4 libqwt) # libqwt-qt4)
set(QWT_NAMES ${QWT_NAMES} qwt libqwt)

find_library(QWT_LIBRARY
  NAMES ${QWT_NAMES}
  PATHS $ENV{QWT_DIR}/lib NO_DEFAULT_PATH)

find_library(QWT_LIBRARY
  NAMES ${QWT_NAMES}
  PATHS ${QWT_DIR}/lib ${QWT_DIR}/lib64 opt/qwt/lib /usr/local/qwt/lib /usr/local/lib /usr/lib)

if(QWT_INCLUDE_DIR AND QWT_LIBRARY)
  set(QWT_LIBRARIES ${QWT_LIBRARY})
  set(QWT_FOUND "YES")
  if (CYGWIN)
    if(NOT BUILD_SHARED_LIBS)
      set(QWT_DEFINITIONS -DQWT_STATIC)
    endif(NOT BUILD_SHARED_LIBS)
  endif(CYGWIN)
endif(QWT_INCLUDE_DIR AND QWT_LIBRARY)

mark_as_advanced(QWT_INCLUDE_DIR QWT_LIBRARY QWT_DIR)
