add_executable(Kozmic main.cpp)

target_link_libraries(Kozmic Core)
target_include_directories(Kozmic PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Kozmic PUBLIC ${INCLUDE_DIR})
