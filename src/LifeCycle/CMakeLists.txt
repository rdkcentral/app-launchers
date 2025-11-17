set(LIFECYCLE_SOURCES LifeCycleCLI.cpp)

add_library(LifeCycle STATIC ${LIFECYCLE_SOURCES})

target_include_directories(LifeCycle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(LifeCycle PRIVATE ${CMAKE_SOURCE_DIR}/src/Interfaces)
