add_executable(scene_test test.cpp)
target_link_libraries(scene_test PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}_scene)
add_test(NAME scene_test COMMAND scene_test)