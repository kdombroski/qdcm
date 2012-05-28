include(add_includes)

#add_definitions(-Wall)

if(NOT ${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_definitions(-DQT_NO_DEBUG)
endif()

if(QDCM_BUILD_TESTS AND EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/test/")
    # Get all header files
    file(GLOB TEST_HDRS "${CMAKE_CURRENT_SOURCE_DIR}/test/*.h")

    foreach (TEST ${TEST_HDRS})
        # Creating custom file
        get_filename_component(FILENAME ${TEST} NAME_WE)

        # Generate Qt moc file
        qt4_wrap_cpp(MOC_${FILENAME} ${TEST})

        # Generate test main source file
        set(TEST_SRC "${CMAKE_CURRENT_BINARY_DIR}/test/test_${FILENAME}.cpp")
        if(WIN32)
            add_custom_command(
                OUTPUT "${TEST_SRC}"
                COMMAND ${CMAKE_COMMAND} -E echo "\#include \\\"${TEST}\\\"" > ${TEST_SRC}
                COMMAND ${CMAKE_COMMAND} -E echo "QTEST_MAIN(${FILENAME})" >> ${TEST_SRC}
                DEPENDS ${TEST}
            )
        else(WIN32)
            add_custom_command(
                OUTPUT "${TEST_SRC}"
                COMMAND echo "\"""#include""\\\"${TEST}\\\"" "\"" > ${TEST_SRC}
                COMMAND echo "\"QTEST_MAIN(${FILENAME})\"" >> ${TEST_SRC}
                DEPENDS ${TEST}
            )
        endif(WIN32)

        set(GCOV "")
        if(UNIX AND QDCM_TESTS_COVERAGE)
            add_definitions(--coverage)
            set(GCOV "gcov")
        endif()

        # Link target
        set(TEST_TARGET "${PROJECT_NAME}_${FILENAME}")
        add_executable(${TEST_TARGET} ${TEST_SRC} ${MOC_${FILENAME}} ${TEST})
        target_link_libraries(${TEST_TARGET} ${PROJECT_NAME} ${QT_LIBRARIES} ${QT_QTTEST_LIBRARY} ${QT_QTGUI_LIBRARY} ${LIBS})

        #Link unit-test library and the related library
        target_link_libraries(${TEST_TARGET} ${GCOV})

        add_test(${TEST_TARGET} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${TEST_TARGET})
    endforeach()

endif()

