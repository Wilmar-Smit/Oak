find_package(Catch2 3 REQUIRED)

file(GLOB_RECURSE OAK_TEST_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

if(OAK_TEST_SOURCES)
    add_executable(oak_tests ${OAK_TEST_SOURCES})

    target_link_libraries(oak_tests
        PRIVATE
            oak
            Catch2::Catch2WithMain
    )

    target_include_directories(oak_tests PRIVATE "${PROJECT_SOURCE_DIR}/src")

    include(Catch)
    catch_discover_tests(oak_tests)
endif()
