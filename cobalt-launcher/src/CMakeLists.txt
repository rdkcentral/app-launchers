# If not stated otherwise in this file or this component's LICENSE file the
# following copyright and licenses apply:
#
# Copyright 2025 RDK Management
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set(ROOT_SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${ROOT_SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/src/Interfaces)

add_subdirectory(CobaltLauncher)
target_link_libraries(${PROJECT_NAME} PRIVATE CobaltLauncher)

option(MOCK_LIFECYCLE "Build with mock Lifecycle implementation" OFF)
if(MOCK_LIFECYCLE)
    message(STATUS "Building in MOCK_LIFECYCLE mode.")
    target_compile_definitions(${PROJECT_NAME} PRIVATE MOCK_LIFECYCLE)
    add_subdirectory(LifeCycle)
    target_link_libraries(${PROJECT_NAME} PRIVATE LifeCycle)
endif()

add_subdirectory(Config)
target_link_libraries(${PROJECT_NAME} PRIVATE Config)
