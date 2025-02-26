set_property(GLOBAL PROPERTY TOPICS_DIR)
function(create_msg_library msg_name)
    set(tmp "${CMAKE_CURRENT_SOURCE_DIR}/src/topics")
    set(MSG_CXX_FILE "${TOPICS_DIR}/${msg_name}.cxx")
    set(MSG_PUBSUB_FILE "${TOPICS_DIR}/${msg_name}PubSubTypes.cxx")
    execute_process(

        COMMAND fastddsgen ${TOPICS_DIR}/${msg_name}.idl -d ${TOPICS_DIR}
    )
    add_library(${msg_name} STATIC ${MSG_CXX_FILE} ${MSG_PUBSUB_FILE})
endfunction()