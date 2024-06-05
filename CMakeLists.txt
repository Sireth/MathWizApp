cmake_minimum_required(VERSION 3.5)
project("MathWizApp" VERSION 0.0.1)

add_subdirectory(external/math_wiz)
add_subdirectory(external/json)

if(EXISTS /usr/bin/gcc-9)
    set(CMAKE_C_COMPILER /usr/bin/gcc-9)
endif ()

if(EXISTS /usr/bin/g++-9)
    set(CMAKE_CXX_COMPILER /usr/bin/g++-9)
endif ()

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MATH_WIZ_APP_INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

set(MATH_WIZ_APP_HEADERS
        include/ErrorHandler.h
        include/VariableHandler.h
)

set(MATH_WIZ_APP_SOURCES
        src/main.cpp

        src/ErrorHandler.cpp
        src/VariableHandler.cpp
)

set(PROJECT_SOURCES
        ${MATH_WIZ_APP_HEADERS}
        ${MATH_WIZ_APP_SOURCES}
)

add_executable(math_wiz_app ${PROJECT_SOURCES})

target_include_directories(math_wiz_app PUBLIC ${MATH_WIZ_APP_INCLUDE_DIRS})

target_link_libraries(math_wiz_app PRIVATE math_wiz PRIVATE nlohmann_json)

