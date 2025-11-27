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

set(COBALT_LAUNCHER_SOURCES CobaltLauncher.cpp)

add_library(CobaltLauncher STATIC ${COBALT_LAUNCHER_SOURCES})

target_include_directories(CobaltLauncher PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(CobaltLauncher PRIVATE ${CMAKE_SOURCE_DIR}/src/Interfaces)

find_library(COBALT_LIBRARY loader_app REQUIRED)
target_link_libraries(CobaltLauncher PRIVATE ${COBALT_LIBRARY})
#add_compile_definitions(MOCK_SB)
