project(tables-api)

add_library(${PROJECT_NAME} SHARED
    src/card.cpp
    src/deck_state.cpp
    src/deck_state_impl.cpp
    src/deck_state_impl.h
    src/make_move.cpp
)

target_include_directories(${PROJECT_NAME} PUBLIC
    include/
)
