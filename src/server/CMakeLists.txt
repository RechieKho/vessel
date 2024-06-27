set(LIBRARY_NAME ${PROJECT_NAME}_server)

add_library(${LIBRARY_NAME} INTERFACE)
target_include_directories(${LIBRARY_NAME} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(${LIBRARY_NAME} INTERFACE ${PROJECT_NAME}_core)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)