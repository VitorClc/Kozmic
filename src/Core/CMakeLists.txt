set (INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/)

##### CLASSES CONFIG #####
add_library(Window STATIC Window.cpp ${INCLUDE_DIR}/Window.h)
target_include_directories(Window PUBLIC ${INCLUDE_DIR})

add_library(Mesh STATIC Mesh.cpp ${INCLUDE_DIR}/Mesh.h)
target_include_directories(Mesh PUBLIC ${INCLUDE_DIR})

##### COMPILING STB_IMAGE #####
add_library(STB stb_image.cpp ${INCLUDE_DIR}/stb_image.h)
target_include_directories(STB PUBLIC ${INCLUDE_DIR})

##### DEPENDENCIES CONFIG #####
set(SDL_DEPS SDL2main SDL2 m user32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32 dinput8 dxerr8)
set(GLEW_DEPS glew32 glu32 opengl32)

## WINDOW
CONFIG_DEPENDENCY(Window SDL2 "${SDL_DEPS}")
CONFIG_DEPENDENCY(Window GLEW "${GLEW_DEPS}")

## Mesh
CONFIG_DEPENDENCY(Mesh GLEW "${GLEW_DEPS}" )
CONFIG_DEPENDENCY(Mesh GLM glm)
target_link_libraries(Mesh STB)