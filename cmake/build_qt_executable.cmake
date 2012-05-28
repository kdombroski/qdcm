# This script defines rules to build a Qt executable.

file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp")
file(GLOB HDRS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB UIS "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui")
file(GLOB TSS "${CMAKE_CURRENT_SOURCE_DIR}/lang/*.ts")
file(GLOB RES "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qrc")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}/")

if(UNIX)
    add_definitions(-Wall)
endif()

# Look for Qt libraries
find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})
if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DQT_NO_DEBUG)
endif(NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug")
add_definitions(-DQT_FATAL_ASSERT)

# Add dependent includes
include(add_includes)

# Wrap Qt meta-objects
set(META_SRCS "")
foreach (MOC ${MOCS})
    set(META_SRCS ${META_SRCS} include/${MOC})
endforeach()
qt4_wrap_cpp(MOC_SRCS ${META_SRCS})

# Wrap UI
qt4_wrap_ui(UI_SRCS ${UIS})

# Resources
qt4_add_resources(RES_SRCS ${RES})

# Translations
qt4_add_translation(TRANSLATIONS ${TSS})

# Add OPENGL includes
include(add_opengl)

set(GCOV "")
if(UNIX)
    set(GCOV "gcov")
endif()

add_executable(${PROJECT_NAME} ${SRCS} ${MOC_SRCS} ${UI_SRCS} ${RES_SRCS} ${HDRS} ${TRANSLATIONS})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${LIBS} ${GCOV})

# Link OPENGL libraries
include(link_opengl)

install(TARGETS ${PROJECT_NAME}
        RUNTIME
        DESTINATION ${INSTALL_BIN}
        COMPONENT runtime)

if(MSVC)
    if(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
        install(FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.pdb"
                DESTINATION ${INSTALL_BIN}
                COMPONENT runtime)
    endif()
endif()
