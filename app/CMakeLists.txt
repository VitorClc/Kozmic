set (DEPENDENCIES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/dependencies)

function(CONFIG_DEPENDENCY DEP_NAME LIBS)
    message("Configuring " ${DEP_NAME})
    message(${DEPENDENCIES_DIR}/${ARCH}/${DEP_NAME}/)
    target_include_directories(Kozmic PUBLIC ${DEPENDENCIES_DIR}/include/${DEP_NAME}/)
    target_link_directories(Kozmic PUBLIC ${DEPENDENCIES_DIR}/${ARCH}/${DEP_NAME}/)
    target_link_libraries(Kozmic ${LIBS})
endfunction()

add_executable(Kozmic main.cpp)

##### DEPENDENCIES CONFIG #####
set(SDL_DEPS SDL2main SDL2 m user32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32 dinput8 dxerr8)
CONFIG_DEPENDENCY(SDL2 "${SDL_DEPS}")

set(GLEW_DEPS glew32 glu32 opengl32)
CONFIG_DEPENDENCY(GLEW "${GLEW_DEPS}")