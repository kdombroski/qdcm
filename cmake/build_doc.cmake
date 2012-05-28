find_package(Doxygen)

configure_file(${QDCM_SOURCE_DIR}/doxygen/doxy.config.in ${CMAKE_CURRENT_BINARY_DIR}/doxy.config @ONLY)

set(DOXY_CONFIG "${CMAKE_CURRENT_BINARY_DIR}/doxy.config")

add_custom_target(${PROJECT_NAME}_doc ${DOXYGEN_EXECUTABLE} ${DOXY_CONFIG})
add_dependencies(doc ${PROJECT_NAME}_doc)

