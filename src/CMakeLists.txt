set (DEPENDENCIES_DIR C:/Users/vitor/Desktop/dependencies) #CHANGE TO THE DEPENDENCIES DIRECTORY

function(CONFIG_DEPENDENCY TARGET DEP_NAME LIBS)
    message("Configuring " ${DEP_NAME})
    #message(${DEPENDENCIES_DIR}/${ARCH}/${DEP_NAME}/)
    target_include_directories(${TARGET} PUBLIC ${DEPENDENCIES_DIR}/include/${DEP_NAME}/)
    target_link_directories(${TARGET} PUBLIC ${DEPENDENCIES_DIR}/${ARCH}/${DEP_NAME}/)
    target_link_libraries(${TARGET} ${LIBS})
endfunction()

add_subdirectory(Core)
