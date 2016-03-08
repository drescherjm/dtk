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

cmake_minimum_required(VERSION 2.8.11)

######################################################################

if(${CMAKE_MAJOR_VERSION} GREATER 2)
  cmake_policy(SET CMP0028 NEW)
endif(${CMAKE_MAJOR_VERSION} GREATER 2)

######################################################################

project(dtk)

## ###################################################################
## Version setup
## ###################################################################

set(dtk_VERSION_MAJOR 1)
set(dtk_VERSION_MINOR 0)
set(dtk_VERSION_PATCH 0)
set(dtk_VERSION
  ${dtk_VERSION_MAJOR}.${dtk_VERSION_PATCH}.${dtk_VERSION_PATCH})

## ###################################################################
## Path setup
## ###################################################################

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)

## #################################################################
## Build type setup
## #################################################################

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE RelWithDebInfo CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

## #################################################################
## Install prefix
## #################################################################

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/install" CACHE PATH "${PROJECT_NAME} install prefix" FORCE)
endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

## #################################################################
## Generate compilation database
## #################################################################

set(CMAKE_EXPORT_COMPILE_COMMANDS "ON")

## ###################################################################
## Build setup
## ###################################################################

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(GNUInstallDirs)
include(GenerateExportHeader)
include(CheckCXXCompilerFlag)

check_cxx_compiler_flag("-std=c++11" COMPILER_SUPPORTS_CXX11)
check_cxx_compiler_flag("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wno-unknown-pragmas")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wno-unknown-pragmas")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas")
  message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support.")
endif()

if(CMAKE_COMPILER_IS_GNUCXX AND DTK_ENABLE_COVERAGE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
  set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
endif(CMAKE_COMPILER_IS_GNUCXX AND DTK_ENABLE_COVERAGE)

if(CMAKE_SIZEOF_VOID_P MATCHES 8)
  set(DTK_BUILD_32 0)
  set(DTK_BUILD_64 1)
else(CMAKE_SIZEOF_VOID_P MATCHES 8)
  set(DTK_BUILD_32 1)
  set(DTK_BUILD_64 0)
endif(CMAKE_SIZEOF_VOID_P MATCHES 8)

## #################################################################
## CMake dependencies
## #################################################################

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

## #################################################################
## Options
## #################################################################

option(DTK_ENABLE_COVERAGE              "enable coverage report" false)
option(DTK_COVERAGE_USE_COBERTURA "use cobertura coverage format" true)
option(DTK_ENABLE_MEMCHECK     "enable valgrind memcheck report" false)

option(DTK_BUILD_COMPOSER            "Build composer layer" false)
option(DTK_BUILD_DISTRIBUTED         "Build distributed layer" true)
option(DTK_BUILD_SCRIPT              "Build script layer"  false)
option(DTK_BUILD_WRAPPERS            "Build wrappers"      false)
option(DTK_BUILD_SUPPORT_CORE        "Build support layer" false)
option(DTK_BUILD_SUPPORT_CONTAINER   "Build support layer" false)
option(DTK_BUILD_SUPPORT_COMPOSER    "Build support layer" false)
option(DTK_BUILD_SUPPORT_DISTRIBUTED "Build support layer" false)
option(DTK_BUILD_SUPPORT_GUI         "Build support layer" false)
option(DTK_BUILD_SUPPORT_MATH        "Build support layer" false)
option(DTK_BUILD_SUPPORT_PLOT        "Build support layer" false)
option(DTK_BUILD_SUPPORT_VR          "Build support layer" false)

## ###################################################################
## Test setup
## ###################################################################

if(DTK_ENABLE_MEMCHECK)

  find_program(CTEST_MEMORYCHECK_COMMAND valgrind)
  set(CTEST_MEMORYCHECK_COMMAND_OPTIONS "--trace-children=yes --leak-check=full --xml=yes --suppressions=${CMAKE_SOURCE_DIR}/tst/gtk.suppressions  --xml-file=valgrind-%p.xml")

  function(add_test name binary)
    set(memcheck_command "${CTEST_MEMORYCHECK_COMMAND} ${CTEST_MEMORYCHECK_COMMAND_OPTIONS}")
    separate_arguments(memcheck_command)
    _add_test(${name}_memcheck ${memcheck_command} ${binary} ${ARGN})
  endfunction(add_test)

  function(set_memcheck_test_properties name)
    set_tests_properties(${name}_memcheck ${ARGN})
  endfunction(set_memcheck_test_properties)

endif(DTK_ENABLE_MEMCHECK)

enable_testing()

if(DTK_ENABLE_COVERAGE)
  include(dtkCodeCoverage)
  include(FindPythonInterp)

  if(DTK_COVERAGE_USE_COBERTURA)
    SETUP_TARGET_FOR_COVERAGE_COBERTURA(cov ctest coverage)
  else(DTK_COVERAGE_USE_COBERTURA)
    SETUP_TARGET_FOR_COVERAGE(cov ctest coverage)
  endif(DTK_COVERAGE_USE_COBERTURA)

endif(DTK_ENABLE_COVERAGE)

## #################################################################
## Dependencies
## #################################################################

find_package(Qt5Core REQUIRED)
find_package(Qt5Concurrent REQUIRED)
find_package(Qt5Quick REQUIRED)
find_package(Qt5Network REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Test REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5Svg REQUIRED)

set(CMAKE_AUTOMOC ON)

## ###################################################################
## Doc setup
## ###################################################################

set(dtk_INSTALL_DOCS ${CMAKE_BINARY_DIR}/html)
set(dtk_CONFIG_DOCS  ${CMAKE_BINARY_DIR}/doc/cfg)

get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake LOCATION)
get_filename_component(QT5_BINARY_DIR ${QT5_QMAKE_EXECUTABLE} PATH)

## #################################################################
## Wrapping
## #################################################################

if(DTK_BUILD_WRAPPERS)

## #################################################################
## Swig
## #################################################################

mark_as_advanced(SWIG_DIR)
mark_as_advanced(SWIG_EXECUTABLE)
mark_as_advanced(SWIG_VERSION)

find_package(SWIG REQUIRED)

if(SWIG_FOUND)
  include(${SWIG_USE_FILE})
  set(CMAKE_SWIG_FLAGS "")

  macro(dtk_wrap project target name language input deps)

    set(wrap_output ${project}_wrap_${language}.cpp)

    add_custom_command(
      OUTPUT ${wrap_output}
      COMMAND ${SWIG_EXECUTABLE}
      ARGS
      "-${language}"
      "-c++"
      "-module" ${name}
      "-I${PROJECT_SOURCE_DIR}/.."
      "-I${PROJECT_SOURCE_DIR}/"
      "-I${dtk_SOURCE_DIR}/"
      "-I${dtk_SOURCE_DIR}/src"
      "-I${dtk_SOURCE_DIR}/src/dtkCoreSupport"
      "-outdir" ${CMAKE_CURRENT_BINARY_DIR}
      "-o" ${wrap_output}
      ${input}
      MAIN_DEPENDENCY ${input}
      COMMENT "Wrapping ${input} to ${language}")

    set(${target} ${${target}} ${wrap_output})

  endmacro(dtk_wrap)

else(SWIG_FOUND)

  message("DTK_BUILD_WRAPPERS options requires SWIG.")

endif(SWIG_FOUND)

if(SWIG_FOUND)
  add_definitions(-DHAVE_SWIG)
endif(SWIG_FOUND)

## #################################################################
## Tcl
## #################################################################

find_package(TCL QUIET)

if(TCL_FOUND)
  include_directories(${TCL_INCLUDE_PATH})
endif(TCL_FOUND)

if(TCL_FOUND)
  add_definitions(-DHAVE_TCL) # Towards deprecation
  set(DTK_HAVE_TCL 1)
else(TCL_FOUND)
  set(DTK_HAVE_TCL 0)
endif(TCL_FOUND)

## #################################################################
## Python
## #################################################################

find_package(PythonLibs QUIET)

if(PYTHONLIBS_FOUND)
  include_directories(${PYTHON_INCLUDE_DIRS})
  get_filename_component(PYTHON_PATH ${PYTHON_LIBRARIES} PATH)
  link_directories(${PYTHON_PATH})
  add_definitions(-DHAVE_PYTHON) # Towards deprecation
  set(DTK_HAVE_PYTHON 1)
else(PYTHONLIBS_FOUND)
  set(DTK_HAVE_PYTHON 0)
endif(PYTHONLIBS_FOUND)

## #################################################################
## Build wrappers (end)
## #################################################################

endif(DTK_BUILD_WRAPPERS)

## #################################################################
## Dependencies - Optional                           [TO BE REMOVED]
## #################################################################

set(DTK_HAVE_MPI "NO")

if(DTK_BUILD_SUPPORT_DISTRIBUTED)

find_package(MPI QUIET)

if(MPI_FOUND)
  include_directories(${MPI_INCLUDE_PATH})
  set(COMPILE_FLAGS ${COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
  set(DTK_HAVE_MPI "YES")
endif(MPI_FOUND)

endif(DTK_BUILD_SUPPORT_DISTRIBUTED)

set(DTK_HAVE_ZLIB "NO")

find_package(ZLIB QUIET)
if(ZLIB_FOUND)
  include_directories( ${ZLIB_INCLUDE_DIRS} )
  set(DTK_HAVE_ZLIB "YES")
endif(ZLIB_FOUND)

set(DTK_HAVE_VRPN "NO")

if(DTK_BUILD_SUPPORT_VR)

## #################################################################
## OpenNI / Nite && VRPN
## #################################################################

find_path(OPENNI_INCLUDES XnOpenNI.h /usr/include/ni)
find_path(  NITE_INCLUDES XnVNite.h  /usr/include/nite)

if(OPENNI_INCLUDES AND NITE_INCLUDES)
  include_directories(/usr/include/ni)
  include_directories(/usr/include/nite)
endif(OPENNI_INCLUDES AND NITE_INCLUDES)

find_library(OPENNI_LIBRARY NAMES OpenNI  PATHS /usr/lib)
find_library(  NITE_LIBRARY NAMES XnVNite PATHS /usr/lib)

if(OPENNI_LIBRARY AND NITE_LIBRARY)
  link_directories(/usr/lib)
endif(OPENNI_LIBRARY AND NITE_LIBRARY)

if(OPENNI_INCLUDES AND NITE_INCLUDES AND NOT DEFINED DTK_HAVE_NITE)
  set(DTK_HAVE_NITE "YES")
else(OPENNI_INCLUDES AND NITE_INCLUDES AND NOT DEFINED DTK_HAVE_NITE)
  set(DTK_HAVE_NITE "NO")
endif(OPENNI_INCLUDES AND NITE_INCLUDES AND NOT DEFINED DTK_HAVE_NITE)

mark_as_advanced(OPENNI_INCLUDES)
mark_as_advanced(NITE_INCLUDES)

mark_as_advanced(OPENNI_LIBRARY)
mark_as_advanced(NITE_LIBRARY)

## #################################################################
## Vrpn
## #################################################################

find_path(QUAT_INCLUDES           quat.h /usr/include /usr/local/include)
find_path(VRPN_INCLUDES vrpn_Configure.h /usr/include /usr/local/include)

if(QUAT_INCLUDES AND VRPN_INCLUDES)
include_directories(${QUAT_INCLUDES})
include_directories(${VRPN_INCLUDES})
endif(QUAT_INCLUDES AND VRPN_INCLUDES)

mark_as_advanced(VRPN_INCLUDES)
mark_as_advanced(QUAT_INCLUDES)

find_library(QUAT_LIBRARY NAMES quat PATHS /usr/lib /usr/local/lib)
find_library(VRPN_LIBRARY NAMES vrpn PATHS /usr/lib /usr/local/lib)

if(QUAT_LIBRARY AND VRPN_LIBRARY)
  add_definitions(-DHAVE_VRPN)
  set(DTK_HAVE_VRPN "YES")
endif(QUAT_LIBRARY AND VRPN_LIBRARY)

mark_as_advanced(QUAT_LIBRARY)
mark_as_advanced(VRPN_LIBRARY)

endif(DTK_BUILD_SUPPORT_VR)

## #################################################################
## Dependencies - internal
## #################################################################

include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtk)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkComposer)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkMonitoring)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkCore)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkDistributed)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkLog)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkMath)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkMeta)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkScript)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/dtkTest)

## ###################################################################
## Input
## ###################################################################

add_subdirectory(src)
add_subdirectory(tst)
add_subdirectory(app)
add_subdirectory(doc)

## ###################################################################
## Exporting
## ###################################################################

export(PACKAGE dtk)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dtkConfig.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/dtkConfig.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dtkConfig.install.cmake.in
  "${PROJECT_BINARY_DIR}/install/dtkConfig.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dtkConfigVersion.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/dtkConfigVersion.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dtkSetTestEnvironment.cmake.in
"${CMAKE_CURRENT_BINARY_DIR}/dtkSetTestEnvironment.cmake" @ONLY)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/dtkCodeCoverage.cmake
"${CMAKE_CURRENT_BINARY_DIR}/dtkCodeCoverage.cmake" @ONLY)

set_directory_properties(PROPERTIES TEST_INCLUDE_FILE "${CMAKE_CURRENT_BINARY_DIR}/dtkSetTestEnvironment.cmake")

install(FILES
  "${CMAKE_CURRENT_BINARY_DIR}/install/dtkConfig.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/dtkConfigVersion.cmake"
  "${CMAKE_CURRENT_BINARY_DIR}/dtkCodeCoverage.cmake"
  DESTINATION  ${CMAKE_INSTALL_LIBDIR}/cmake/dtk)

install(EXPORT dtkDepends DESTINATION  ${CMAKE_INSTALL_LIBDIR}/cmake/dtk)

## ###################################################################
## Beautifying
## ###################################################################

mark_as_advanced(dtk_VERSION_MAJOR)
mark_as_advanced(dtk_VERSION_MINOR)
mark_as_advanced(dtk_VERSION_BUILD)

mark_as_advanced(Qt5_DIR)
mark_as_advanced(Qt5Concurrent_DIR)
mark_as_advanced(Qt5Core_DIR)
mark_as_advanced(Qt5Gui_DIR)
mark_as_advanced(Qt5Network_DIR)
mark_as_advanced(Qt5Qml_DIR)
mark_as_advanced(Qt5Quick_DIR)
mark_as_advanced(Qt5QuickTest_DIR)
mark_as_advanced(Qt5Script_DIR)
mark_as_advanced(Qt5Test_DIR)
mark_as_advanced(Qt5Widgets_DIR)
mark_as_advanced(Qt5Xml_DIR)
mark_as_advanced(Qt5XmlPatterns_DIR)

mark_as_advanced(CMAKE_AR)
mark_as_advanced(CMAKE_BUILD_TYPE)
mark_as_advanced(CMAKE_INSTALL_PREFIX)
mark_as_advanced(CMAKE_OSX_ARCHITECTURES)
mark_as_advanced(CMAKE_OSX_DEPLOYMENT_TARGET)
mark_as_advanced(CMAKE_OSX_SYSROOT)
mark_as_advanced(CTEST_MEMORYCHECK_COMMAND)

mark_as_advanced(DTK_ENABLE_COVERAGE)
mark_as_advanced(DTK_ENABLE_MEMCHECK)
mark_as_advanced(DTK_COVERAGE_USE_COBERTURA)

## ###################################################################
## Packaging
## ###################################################################

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_VERSION_MAJOR "${dtk_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${dtk_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${dtk_VERSION_PATCH}")

include(CPack)

######################################################################
### CMakeLists.txt ends here
