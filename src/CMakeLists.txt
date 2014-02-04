### CMakeLists.txt ---

add_subdirectory(dtk)
add_subdirectory(dtkCore)
add_subdirectory(dtkDistributed)
add_subdirectory(dtkLog)
add_subdirectory(dtkMath)
add_subdirectory(dtkTest)
add_subdirectory(dtkWidgets)

add_subdirectory(dtkCoreSupport)
add_subdirectory(dtkDistributedSupport)
add_subdirectory(dtkGuiSupport)
add_subdirectory(dtkMathSupport)

set(DTK_TARGETS)
set(DTK_TARGETS ${DTK_TARGETS} dtkCore)
set(DTK_TARGETS ${DTK_TARGETS} dtkDistributed)
set(DTK_TARGETS ${DTK_TARGETS} dtkLog)
set(DTK_TARGETS ${DTK_TARGETS} dtkMath)
set(DTK_TARGETS ${DTK_TARGETS} dtkWidgets)

set(DTK_TARGETS ${DTK_TARGETS} dtkCoreSupport)
set(DTK_TARGETS ${DTK_TARGETS} dtkGuiSupport)
set(DTK_TARGETS ${DTK_TARGETS} dtkMathSupport)

export(TARGETS ${DTK_TARGETS} FILE "${CMAKE_BINARY_DIR}/dtkDepends.cmake")
