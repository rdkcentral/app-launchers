set(ROOT_SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${ROOT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/Interfaces)

add_subdirectory(CobaltLauncher)
target_link_libraries(${PROJECT_NAME} PRIVATE CobaltLauncher)

add_subdirectory(LifeCycle)
target_link_libraries(${PROJECT_NAME} PRIVATE LifeCycle)

add_subdirectory(Config)
target_link_libraries(${PROJECT_NAME} PRIVATE Config)
