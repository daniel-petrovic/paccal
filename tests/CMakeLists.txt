include(FetchContent)

FetchContent_Declare (
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.7.1
)

FetchContent_MakeAvailable(Catch2)

list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)

enable_testing()

add_executable(tests test.cpp)
target_link_libraries(tests
    PRIVATE
        Catch2::Catch2WithMain
        libpacc 
    )

target_include_directories (tests
    PRIVATE 
        $<BUILD_INTERFACE: $<TARGET_PROPERTY:libpacc,INCLUDE_DIRECTORIES>>
)

include(CTest)
include(Catch)
catch_discover_tests(tests)