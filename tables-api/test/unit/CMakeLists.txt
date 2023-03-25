add_executable(tables_api_unit
    test_deal.cpp
)

target_link_libraries(
    tables_api_unit
    tables-api
    GTest::gtest_main
    GTest::gmock_main
)

gtest_discover_tests(tables_api_unit)
