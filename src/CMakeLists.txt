set(CORE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/core)
set(SERVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/server)
set(SCENE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/scene)

add_subdirectory(${CORE_DIR})
add_subdirectory(${SERVER_DIR})

add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_link_libraries(${PROJECT_NAME} 
    PRIVATE 
        ${PROJECT_NAME}_core ${PROJECT_NAME}_server ${PROJECT_NAME}_scene
)