set(CONFIG_SOURCES JsonConfig.cpp)

add_library(Config STATIC ${CONFIG_SOURCES})

target_include_directories(Config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Config PRIVATE ${CMAKE_SOURCE_DIR}/src/Interfaces)

find_package(RapidJSON REQUIRED)
target_include_directories(Config PUBLIC ${RapidJSON_INCLUDE_DIRS})
