set (INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/Core)

set (SOURCES 
    Window.cpp 
    Mesh.cpp 
    stb_image.cpp
    Camera.cpp
    GameObject.cpp
    Shader.cpp
    Transform.cpp
    Scene.cpp
    ScriptBase.cpp
    Timer.cpp
)

set (INCLUDES 
    ${INCLUDE_DIR}/Window.h 
    ${INCLUDE_DIR}/Mesh.h 
    ${INCLUDE_DIR}/stb_image.h
    ${INCLUDE_DIR}/Camera.h
    ${INCLUDE_DIR}/GameObject.h
    ${INCLUDE_DIR}/Shader.h
    ${INCLUDE_DIR}/Transform.h
    ${INCLUDE_DIR}/Scene.h
    ${INCLUDE_DIR}/ScriptBase.h
    ${INCLUDE_DIR}/Timer.h
)

add_library(Core STATIC ${SOURCES} ${INCLUDES})
target_include_directories(Core PUBLIC ${INCLUDE_DIR})

##### DEPENDENCIES CONFIG #####
set(SDL_DEPS SDL2main SDL2 m user32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32 dinput8 dxerr8)
set(GLEW_DEPS glew32 glu32 opengl32)
set(ASSIMP_DEPS assimp IrrXML zlibstatic)

CONFIG_DEPENDENCY(Core SDL2 "${SDL_DEPS}")
CONFIG_DEPENDENCY(Core GLEW "${GLEW_DEPS}")
CONFIG_DEPENDENCY(Core GLM glm)
CONFIG_DEPENDENCY(Core ASSIMP "${ASSIMP_DEPS}")