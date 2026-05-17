# warehouse_project/tests/CMakeLists.txt
# Unit tests
set(TEST_SOURCES
    test_product.cpp
    test_stock.cpp
    test_user.cpp
    test_incoming_operation.cpp
    test_outgoing_operation.cpp
    test_logger.cpp
    test_order_calculator.cpp
    test_report_generator.cpp
    test_strategy.cpp
    test_scenarios.cpp
)

# Создание исполняемого файла тестов
add_executable(WarehouseTests ${TEST_SOURCES})

# Подключение библиотек
target_link_libraries(WarehouseTests 
    WarehouseLib
    Catch2::Catch2WithMain
)

target_include_directories(WarehouseTests PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/src
)

# Добавление теста в CTest
add_test(NAME WarehouseTests COMMAND WarehouseTests)