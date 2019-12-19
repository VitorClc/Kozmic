set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

##### CLASSES CONFIG #####
add_library(Window STATIC Window.cpp ${INCLUDE_DIR}/Window.h)
target_include_directories(Window PUBLIC ${INCLUDE_DIR})

##### DEPENDENCIES CONFIG #####

## WINDOW
set(SDL_DEPS SDL2main SDL2 m user32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32 dinput8 dxerr8)
CONFIG_DEPENDENCY(Window SDL2 "${SDL_DEPS}")

set(GLEW_DEPS glew32 glu32 opengl32)
CONFIG_DEPENDENCY(Window GLEW "${GLEW_DEPS}")

#CONFIG_DEPENDENCY(GLM glm)