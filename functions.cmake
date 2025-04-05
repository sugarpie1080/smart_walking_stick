set_property(GLOBAL PROPERTY TOPICS_DIR)
function(create_msg_library msg_name)

    file(GLOB MSG_FILES "${TOPICS_DIR}/${msg_name}*.cxx")
    message(INFO  "${MSG_FILES}")
    execute_process(

        COMMAND fastddsgen ${TOPICS_DIR}/${msg_name}.idl -d ${TOPICS_DIR} -python
    )
    add_library(${msg_name} STATIC ${MSG_FILES})
    target_link_libraries(${msg_name} fastdds fastcdr)
    set_property(TARGET ${msg_name} PROPERTY CXX_STANDARD 11)

    set(${msg_name}_MODULE ${msg_name}Wrapper)
    set(${msg_name}_MODULE_FILES  ${TOPICS_DIR}/${msg_name}.i)

    SET_SOURCE_FILES_PROPERTIES(${${msg_name}_MODULE_FILES}
    PROPERTIES CPLUSPLUS ON
    USE_TARGET_INCLUDE_DIRECTORIES TRUE
    )
    
    SWIG_ADD_LIBRARY(${${msg_name}_MODULE}
    TYPE SHARED
    LANGUAGE python
    SOURCES ${${msg_name}_MODULE_FILES})

    set_property(TARGET ${${msg_name}_MODULE} PROPERTY CXX_STANDARD 11)

    if(UNIX AND CMAKE_SIZEOF_VOID_P EQUAL 8)
        set_property(TARGET ${${msg_name}_MODULE} PROPERTY SWIG_COMPILE_DEFINITIONS SWIGWORDSIZE64)
    endif()

    target_link_libraries(${${msg_name}_MODULE}
    Python3::Module
    fastdds
    ${msg_name}
    )

    execute_process(COMMAND ${PYTHON_EXECUTABLE} -c "from distutils import sysconfig; print(sysconfig.get_python_lib(plat_specific=True, prefix='${CMAKE_INSTALL_PREFIX}'))"
    OUTPUT_VARIABLE _ABS_PYTHON_MODULE_PATH
    OUTPUT_STRIP_TRAILING_WHITESPACE)

    get_filename_component (_ABS_PYTHON_MODULE_PATH ${_ABS_PYTHON_MODULE_PATH} ABSOLUTE)
file (RELATIVE_PATH _REL_PYTHON_MODULE_PATH ${CMAKE_INSTALL_PREFIX} ${_ABS_PYTHON_MODULE_PATH})
SET (PYTHON_MODULE_PATH
    ${_REL_PYTHON_MODULE_PATH}/${msg_name}
    )

    install(TARGETS ${msg_name}
    RUNTIME DESTINATION bin/
    LIBRARY DESTINATION lib/
    ARCHIVE DESTINATION lib/
    )
install(TARGETS ${${msg_name}_MODULE} DESTINATION ${PYTHON_MODULE_PATH})
get_property(support_files TARGET ${${msg_name}_MODULE} PROPERTY SWIG_SUPPORT_FILES)
install(FILES ${support_files} DESTINATION ${PYTHON_MODULE_PATH} RENAME __init__.py)



endfunction()