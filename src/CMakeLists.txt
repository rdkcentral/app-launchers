set(ROOT_SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${ROOT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/Interfaces)

add_subdirectory(Cobalt)
target_link_libraries(${PROJECT_NAME} PRIVATE CobaltLauncher)