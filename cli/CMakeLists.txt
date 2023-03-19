project(cli)

add_executable(${PROJECT_NAME}
    cli.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE tables-api)
