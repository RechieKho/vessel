add_executable(server_test test.cpp)
target_link_libraries(server_test PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}_server)
add_test(NAME server_test COMMAND server_test)