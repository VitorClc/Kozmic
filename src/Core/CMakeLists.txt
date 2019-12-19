set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

##### CLASSES CONFIG #####
add_library(Window STATIC Window.cpp ${INCLUDE_DIR}/Window.h)
target_include_directories(Window PUBLIC ${INCLUDE_DIR})

add_library(Mesh STATIC Mesh.cpp ${INCLUDE_DIR}/Mesh.h)
target_include_directories(Mesh PUBLIC ${INCLUDE_DIR})

add_library(Transform INTERFACE)
target_include_directories(Transform INTERFACE ${INCLUDE_DIR}/Transform.h)

##### DEPENDENCIES CONFIG #####
set(SDL_DEPS SDL2main SDL2 m user32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32 dinput8 dxerr8)
set(GLEW_DEPS glew32 glu32 opengl32)

## WINDOW
CONFIG_DEPENDENCY(Window SDL2 "${SDL_DEPS}")
CONFIG_DEPENDENCY(Window GLEW "${GLEW_DEPS}")

## GLM
CONFIG_DEPENDENCY(Mesh GLEW "${GLEW_DEPS}")
CONFIG_DEPENDENCY(Mesh GLM glm)