include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
FetchContent_MakeAvailable(googletest)

add_executable(emojicppTests parserWorks.cpp)
target_link_libraries(emojicppTests PRIVATE emojicpp gtest_main)

include(GoogleTest)
gtest_discover_tests(emojicppTests)
