add_executable(order_book order_book.cpp)

target_link_libraries(order_book PRIVATE decoder)

install(TARGETS order_book RUNTIME DESTINATION ${PROJECT_SOURCE_DIR}/bin)
