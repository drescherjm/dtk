# Given a variable, adds pch support to suitable files.
# Does nothing if not MSVC

MACRO(ADD_MSVC_PRECOMPILED_HEADER PrecompiledHeader PrecompiledSource SourcesVar)
  IF(MSVC)
    get_filename_component(PrecompiledBasename ${PrecompiledHeader} NAME_WE)
    set(PrecompiledBinary "\$(IntDir)/${PrecompiledBasename}.pch")

    get_filename_component(PchSourceAbsolute ${PrecompiledSource} ABSOLUTE)

    set(AllSources ${${SourcesVar}})
    set(PchSources)

    #Determine files that can use the PCH.
    foreach(fileIt ${AllSources})
        string(REGEX MATCH "(\\.cpp|\\.cxx|\\.c|\\.C|\\.CPP|\\.cc)\$" nameMatch "${fileIt}")
        string(LENGTH "${nameMatch}" nameMatchLength)

        get_filename_component(fileItAbsolute ${fileIt} ABSOLUTE)

        if( ${nameMatchLength} GREATER 0 AND ( NOT (${fileItAbsolute} STREQUAL ${PchSourceAbsolute}) ) )

            LIST(APPEND PchSources ${fileIt})
            MESSAGE(" Added Precompiled header support to ${fileIt}")
        endif( ${nameMatchLength} GREATER 0 AND ( NOT (${fileItAbsolute} STREQUAL ${PchSourceAbsolute}) ) )
    endforeach(fileIt)

    foreach(fileIt ${PchSources})
        set_property(SOURCE "${fileIt}" APPEND PROPERTY
            COMPILE_FLAGS "/Yu\"${PrecompiledBinary}\" /FI\"${PrecompiledBinary}\" /Fp\"${PrecompiledBinary}\"")
        set_property(SOURCE "${fileIt}" APPEND PROPERTY
            OBJECT_DEPENDS "${PrecompiledBinary}")
    endforeach(fileIt)
    
    set_property(SOURCE "${PrecompiledSource}" APPEND PROPERTY
          COMPILE_FLAGS "/Yc\"${PrecompiledHeader}\" /Fp\"${PrecompiledBinary}\"")
    set_property(SOURCE "${PrecompiledSource}" PROPERTY
                                OBJECT_OUTPUTS "${PrecompiledBinary}")

    # Add precompiled header to SourcesVar
    LIST(APPEND ${SourcesVar} ${PrecompiledSource})
ENDIF(MSVC)

ENDMACRO(ADD_MSVC_PRECOMPILED_HEADER)
