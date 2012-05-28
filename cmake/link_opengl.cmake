# This script checks the presence of USE_OPENGL and/or USE_OPENGL flags and
# links corresponding libraries with project target.

# Check OPENGL required
if(USE_OPENGL)

    if(TEST_TARGET)
        target_link_libraries(${TEST_TARGET} ${OPENGL_LIBRARIES})
    else(TEST_TARGET)
        target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES})
    endif(TEST_TARGET)
endif(USE_OPENGL)
