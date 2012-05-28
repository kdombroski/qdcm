foreach(LIB ${LIBS})

    if(${LIB}_INCLUDE_PATH)
        include_directories(${${LIB}_INCLUDE_PATH})
    else()
        message(WARNING "Include path for ${LIB} cannot be determined.")
        include_directories(${QDCM_SOURCE_DIR}/source/${LIB}/include)
    endif()

endforeach()