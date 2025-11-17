set(COBALT_LAUNCHER_SOURCES CobaltLauncher.cpp)

add_library(CobaltLauncher STATIC ${COBALT_LAUNCHER_SOURCES})

target_include_directories(CobaltLauncher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(CobaltLauncher PRIVATE ${CMAKE_SOURCE_DIR}/src/Interfaces)
