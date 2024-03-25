cmake_minimum_required(VERSION 3.16)
project(PongSFML LANGUAGES CXX VERSION 2.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(PongSFML "src/game.cpp"  "src/game.h"  "src/main.cpp" "src/fonts.cpp" "src/fonts.h" "src/objects.cpp" "src/objects.h")
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)

target_link_libraries(PongSFML PRIVATE sfml-graphics)
target_compile_features(PongSFML PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET PongSFML
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:PongSFML>
        VERBATIM)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("== Building in release configuration")
    add_custom_command(
        TARGET PongSFML
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/bin_releases/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}"
        COMMAND ${CMAKE_COMMAND} -E chdir "${CMAKE_BINARY_DIR}/bin" ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/bin_releases/${CMAKE_SYSTEM_NAME}/${CMAKE_SYSTEM_PROCESSOR}/PongSFML_${CMAKE_PROJECT_VERSION_MAJOR}.${CMAKE_PROJECT_VERSION_MINOR}_${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}.tar" .
    )
else()
    message("== Building in ${CMAKE_BUILD_TYPE} configuration")
endif()

install(TARGETS PongSFML)