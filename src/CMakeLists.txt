set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)

enable_testing()
add_subdirectory(${CORE_DIR})

set(LIBRARY_NAME ${PROJECT_NAME})
add_library(${LIBRARY_NAME} INTERFACE)
target_link_libraries(
    ${LIBRARY_NAME}
    INTERFACE
        ${LIBRARY_NAME}_core
)