cmake_minimum_required(VERSION 3.12)

if(USE_EMSCRIPTEN_TOOLCHAIN)
    message("Looking for Emscripten path using SDK...")
    execute_process(
            COMMAND bash -c ". ~/emsdk/emsdk_env.sh > /dev/null && echo -n $EMSCRIPTEN"
            OUTPUT_VARIABLE EMSCRIPTEN_ROOT
    )
    if("${EMSCRIPTEN_ROOT}" STREQUAL "")
        message(FATAL_ERROR "Emscripten not found. Please install Emscripten SDK first.")
    else()
        message("Emscripten root found: ${EMSCRIPTEN_ROOT}")
        message("Setting up Emscripten toolchain...")
        set(CMAKE_TOOLCHAIN_FILE ${EMSCRIPTEN_ROOT}/cmake/Modules/Platform/Emscripten.cmake)
        set(CMAKE_CXX_FLAGS "-s WASM=1")
    endif()
endif()

project(TPFinalAyDAI)

set(CMAKE_CXX_STANDARD 17)

include_directories(src/native/cpp/include)

set(SOURCE_FILES
        src/native/cpp/include/algor/List.hpp
        src/native/cpp/include/algor/Point.hpp
        src/native/cpp/include/algor/Segment.hpp
        src/native/cpp/include/algor/Vector.hpp
        src/native/cpp/algor/Vector.cpp
        src/native/cpp/include/algor/Comparator.hpp
)

set(TESTS_FILES
        src/native/cpp/tests/algor/List.cpp
        src/native/cpp/tests/algor/Point.cpp
        src/native/cpp/tests/algor/Vector.cpp
        src/native/cpp/tests/algor/Segment.cpp
)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    set(WASM_MODULE_NAME WASMModule)

    string(TOLOWER "${CMAKE_BUILD_TYPE}" WASM_BUILD_TYPE)

    set(WASM_BUILD_DIR ${PROJECT_SOURCE_DIR}/web-build-${WASM_BUILD_TYPE}/wasm)

    add_executable(${WASM_MODULE_NAME} ${SOURCE_FILES} src/native/cpp/wasm.cpp)
    add_custom_command(
            TARGET ${WASM_MODULE_NAME}
            POST_BUILD
            COMMAND mkdir ARGS -p ${WASM_BUILD_DIR}
            COMMAND cp ARGS -f -t ${WASM_BUILD_DIR} ${CMAKE_BINARY_DIR}/${WASM_MODULE_NAME}.js ${CMAKE_BINARY_DIR}/${WASM_MODULE_NAME}.wasm
            COMMENT "Built files copied to: ${WASM_BUILD_DIR}"
    )

    if(WASM_BUILD_TYPE MATCHES "^(release|debug)$")
        add_custom_command(
                TARGET ${WASM_MODULE_NAME}
                POST_BUILD
                COMMAND npm ARGS run web-build-${WASM_BUILD_TYPE}
                COMMENT "Building web..."
        )
    endif()
else()
    add_executable(CLI ${SOURCE_FILES} src/native/cpp/cli.cpp src/native/cpp/tests/algor/List.cpp)
endif()

add_executable(Tests
        src/native/cpp/tests/Test.hpp
        src/native/cpp/tests/impl/tests_init.cpp
        ${SOURCE_FILES}
        ${TESTS_FILES}
        src/native/cpp/tests/impl/tests.cpp
)
