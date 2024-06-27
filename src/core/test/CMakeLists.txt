add_executable(core_test test.cpp)
target_link_libraries(core_test PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}_core)
add_test(NAME core_test COMMAND core_test)