file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp")
file(GLOB HDRS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB UIS "${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui")
file(GLOB RES "${CMAKE_CURRENT_SOURCE_DIR}/resources/*.qrc")
file(GLOB TSS "${CMAKE_CURRENT_SOURCE_DIR}/lang/*.ts")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories("${PROJECT_BINARY_DIR}/")

if(UNIX)
    add_definitions(-Wall)
    if(QDCM_BUILD_TESTS AND QDCM_TESTS_COVERAGE)
        add_definitions(--coverage)
    endif()
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
foreach(MOC ${MOCS})
    set(META_SRCS ${META_SRCS} include/${MOC})
endforeach()
set(MOC_SRCS "")#To build test folder library related to unit tests.
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
if(UNIX AND QDCM_TESTS_COVERAGE)
    set(GCOV "gcov")
endif()

add_library(${PROJECT_NAME} SHARED ${SRCS} ${MOC_SRCS} ${UI_SRCS} ${RES_SRCS} ${HDRS} ${TRANSLATIONS})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${LIBS} ${GCOV})

set("${PROJECT_NAME}_INCLUDE_PATH" "${CMAKE_CURRENT_SOURCE_DIR}/include" CACHE INTERNAL "${PROJECT_NAME} includes" FORCE)

# Link OPENGL libraries
include(link_opengl)

file(GLOB LIB_INCLUDES "${CMAKE_CURRENT_SOURCE_DIR}/include/*.*")

install(FILES ${LIB_INCLUDES} DESTINATION "${INSTALL_INCLUDE}/${PROJECT_NAME}" COMPONENT includes)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime
        LIBRARY DESTINATION ${INSTALL_LIB} COMPONENT libraries)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${INSTALL_BIN} COMPONENT runtime
        ARCHIVE DESTINATION ${INSTALL_LIB} COMPONENT libraries
        LIBRARY DESTINATION ${INSTALL_LIB} COMPONENT libraries)

if(MSVC)
    if(${CMAKE_BUILD_TYPE} MATCHES "RelWithDebInfo")
        install(FILES "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.pdb"
                DESTINATION ${INSTALL_BIN}
                COMPONENT runtime)
    endif()
endif()
