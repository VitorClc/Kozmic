set (INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/Core)

set (SOURCES 
    Window.cpp 
    MeshRenderer.cpp 
    stb_image.cpp
    Camera.cpp
    GameObject.cpp
    Shader.cpp
    Transform.cpp
    Scene.cpp
    ScriptBase.cpp
    Light.cpp
)

add_library(Core STATIC ${SOURCES})
target_include_directories(Core PUBLIC ${INCLUDE_DIR})

##### DEPENDENCIES CONFIG #####
set(SDL_DEPS SDL2main SDL2 m user32 winmm imm32 ole32 oleaut32 version uuid advapi32 setupapi shell32 dinput8 dxerr8)
set(GLEW_DEPS glew32 glu32 opengl32)
set(ASSIMP_DEPS assimp IrrXML zlibstatic)

CONFIG_DEPENDENCY(Core SDL2 "${SDL_DEPS}")
CONFIG_DEPENDENCY(Core GLEW "${GLEW_DEPS}")
CONFIG_DEPENDENCY(Core GLM glm)
CONFIG_DEPENDENCY(Core ASSIMP "${ASSIMP_DEPS}")