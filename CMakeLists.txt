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

set(SOURCE_FILES src/cpp/test.hpp)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
    set(WASM_MODULE_NAME WASMModule)

    set(WASM_GENERATED_DIR ${PROJECT_SOURCE_DIR}/src/generated)

    add_executable(${WASM_MODULE_NAME} ${SOURCE_FILES} src/cpp/wasm.cpp)
    add_custom_command(
            TARGET ${WASM_MODULE_NAME}
            POST_BUILD
            COMMAND mkdir ARGS -p ${WASM_GENERATED_DIR}
            COMMAND cp ARGS -f -t ${WASM_GENERATED_DIR} ${CMAKE_BINARY_DIR}/${WASM_MODULE_NAME}.js ${CMAKE_BINARY_DIR}/${WASM_MODULE_NAME}.wasm
            BYPRODUCTS ${WASM_GENERATED_DIR}/${WASM_MODULE_NAME}.js ${WASM_GENERATED_DIR}/${WASM_MODULE_NAME}.wasm
            COMMENT "Built files copied to: ${WASM_GENERATED_DIR}"
    )
else()
    add_executable(CLI ${SOURCE_FILES} src/cpp/cli.cpp)
endif()
