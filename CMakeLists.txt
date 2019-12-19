cmake_minimum_required(VERSION 3.0.0)
project(Kozmic VERSION 0.1.0)

##### SYSTEM DETECTION #####
if (WIN32)
    set(OS Windows)
elseif (UNIX)
    set(OS Linux)
endif ()
############################

#TODO: TEST WITH 32bits
##### SYSTEM ARCHITECTURE #####
if(${OS} MATCHES Windows OR Linux)
    if (${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES AMD64 OR amd64)
        set(ARCH "x64")
    elseif (${CMAKE_HOST_SYSTEM_PROCESSOR} MATCHES x86 OR X86)
        set(ARCH "x86")
    endif ()
endif()
###############################

message("Detected System: " ${OS})
message("Detected Architecture: " ${ARCH})

add_subdirectory(src)
add_subdirectory(tests)