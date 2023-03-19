project(tables-api)

add_library(${PROJECT_NAME} SHARED
    src/card.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
)
