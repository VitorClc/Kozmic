add_executable(Kozmic main.cpp)

target_link_libraries(Kozmic Window Mesh)
target_include_directories(Kozmic PUBLIC ${INCLUDE_DIR})