cmake_minimum_required(VERSION 3.12)

project(TPFinalAyDAI)

fIND_PACKAGE( Boost COMPONENTS system filesystem REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG")

include_directories(
        src/native/cpp/include
)

set(SOURCE_FILES
        src/native/cpp/algor/Vector.cpp
        src/native/cpp/algor/ClosestPairOfPoints_impl/algorithm.cpp
        src/native/cpp/test_cases/TestCasesLoader_impl/ParserShared.cpp
        src/native/cpp/logger/Logger.cpp
        src/native/cpp/logger/Logger_impl/Message.cpp
)

set(TESTS_FILES
        src/native/cpp/tests/algor/Array.cpp
        src/native/cpp/tests/algor/List.cpp
        src/native/cpp/tests/algor/Stack.cpp
        src/native/cpp/tests/algor/Point.cpp
        src/native/cpp/tests/algor/Vector.cpp
        src/native/cpp/tests/algor/Segment.cpp
        src/native/cpp/tests/algor/RBTree.cpp

        src/native/cpp/tests/algor/AnySegmentsIntersect.cpp
        src/native/cpp/tests/algor/GrahamScan_JarvisMarch.cpp
        src/native/cpp/tests/algor/ClosestPairOfPoints.cpp
)

set(CLI_SOURCE_FILES
        src/native/cpp/cli/init_utils.cpp
        src/native/cpp/cli/constants.cpp
        src/native/cpp/cli/logger_setup.cpp
)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++")

add_executable(TPFinalAyDAI ${SOURCE_FILES} ${CLI_SOURCE_FILES} src/native/cpp/cli.cpp)

add_executable(Tests
        src/native/cpp/tests/impl/tests_init.cpp
        ${SOURCE_FILES}
        ${TESTS_FILES}
        src/native/cpp/tests/impl/tests.cpp
)

target_link_libraries(TPFinalAyDAI
        ${Boost_LIBRARIES}
)
target_link_libraries(Tests
        ${Boost_LIBRARIES}
)
