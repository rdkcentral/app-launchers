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

set(CONFIG_SOURCES JsonConfig.cpp)

add_library(Config STATIC ${CONFIG_SOURCES})

target_include_directories(Config PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(Config PRIVATE ${CMAKE_SOURCE_DIR}/src/Interfaces)

find_package(RapidJSON REQUIRED)
target_include_directories(Config PUBLIC ${RapidJSON_INCLUDE_DIRS})
