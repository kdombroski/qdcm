# This script checks the presence of flag USE_OPENGL
# and adds corresponding includes for the build
# agains OPENGL library

if(USE_OPENGL)

    find_package(OpenGL REQUIRED)

    # find_package above does not find GL include path on Windows platform
    # so we have to do it manually assuming that CMAKE_INCLUDE_PATH is set
    # correctly to %INCLUDE% variable.
    if(WIN32 AND NOT MINGW)
        find_path(OPENGL_INCLUDE_CUSTOM_DIR GL/gl.h)
        set(OPENGL_INCLUDE_DIR ${OPENGL_INCLUDE_DIR} ${OPENGL_INCLUDE_CUSTOM_DIR})
        include_directories(${OPENGL_INCLUDE_DIR})
    endif()
endif(USE_OPENGL)
