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

target_compile_options(warehouse_app PRIVATE -Wall -Wextra)