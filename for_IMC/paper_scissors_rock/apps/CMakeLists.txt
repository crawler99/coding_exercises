add_executable(screen_game screen_game.cc)

target_link_libraries(screen_game PRIVATE paper_scissors_rock)

install(TARGETS screen_game RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
