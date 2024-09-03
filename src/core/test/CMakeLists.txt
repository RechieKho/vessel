add_executable(core_list_test list_test.cpp)
target_link_libraries(core_list_test PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}_core)
add_test(NAME core_list_test COMMAND core_list_test)

add_executable(core_map_test map_test.cpp)
target_link_libraries(core_map_test PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}_core)
add_test(NAME core_map_test COMMAND core_map_test)

add_executable(core_holder_test holder_test.cpp)
target_link_libraries(core_holder_test PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}_core)
add_test(NAME core_holder_test COMMAND core_holder_test)