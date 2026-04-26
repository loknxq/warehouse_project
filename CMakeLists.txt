cmake_minimum_required(VERSION 3.10)
project(WarehouseManagementSystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_language(CXX)

set(SOURCES
    src/main.cpp
    src/core/Product.cpp
    src/core/Stock.cpp
    src/core/Supplier.cpp
    src/core/User.cpp
    src/documents/IncomingOperation.cpp
    src/documents/OutgoingOperation.cpp
    src/services/Logger.cpp
    src/services/OrderCalculator.cpp
    src/services/ReportGenerator.cpp
    src/strategies/AverageSalesStrategy.cpp
)

add_executable(warehouse_app ${SOURCES})

target_include_directories(warehouse_app PRIVATE include)

# Если SQLite3 и pthread не нужны для демонстрации, можно закомментировать эти строки
# Для полноценного проекта с базой данных их следует раскомментировать
# find_package(SQLite3 REQUIRED)
# find_package(Threads REQUIRED)
# target_link_libraries(warehouse_app SQLite::SQLite3 Threads::Threads)

# Опциональные флаги предупреждений
target_compile_options(warehouse_app PRIVATE -Wall -Wextra)