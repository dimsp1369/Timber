cmake_minimum_required(VERSION 3.28)
project(timber)

set(CMAKE_CXX_STANDARD 17)

add_executable(timber code/Timber.cpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/SFML/lib/cmake/SFML")
find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

file(COPY fonts graphics sound DESTINATION ${CMAKE_BINARY_DIR})

if (WIN32)
    add_custom_command(TARGET timber POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${PROJECT_SOURCE_DIR}/OpenAL32.dll"
            $<TARGET_FILE_DIR:timber>)
endif()

include_directories("C:/SFML/include")
target_link_libraries(timber sfml-graphics sfml-window sfml-system sfml-audio sfml-network)


