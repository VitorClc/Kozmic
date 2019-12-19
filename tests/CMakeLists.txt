add_executable(Kozmic main.cpp)

target_link_libraries(Kozmic Window)
target_include_directories(Kozmic PUBLIC ${INCLUDE_DIR})