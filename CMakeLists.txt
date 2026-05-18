cmake_minimum_required(VERSION 3.14)
project(WarehouseProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    src/core/Product.cpp
    src/core/Stock.cpp
    src/core/User.cpp
    src/core/Supplier.cpp
    src/documents/Document.cpp
    src/documents/IncomingOperation.cpp
    src/documents/OutgoingOperation.cpp
    src/services/Logger.cpp
    src/services/OrderCalculator.cpp
    src/services/ReportGenerator.cpp
    src/strategies/AverageSalesStrategy.cpp
)

foreach(SOURCE_FILE ${SOURCES})
    if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE_FILE})
        message(WARNING "Source file not found: ${SOURCE_FILE}")
    endif()
endforeach()

add_library(WarehouseLib STATIC ${SOURCES})

target_include_directories(WarehouseLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(WarehouseApp src/main.cpp)
target_link_libraries(WarehouseApp WarehouseLib)

option(BUILD_TESTS "Build unit tests" ON)

if(BUILD_TESTS)
    enable_testing()
    
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
    )
    FetchContent_MakeAvailable(Catch2)
    
    set(TEST_SOURCES
        tests/test_product.cpp
        tests/test_stock.cpp
        tests/test_user.cpp
        tests/test_supplier.cpp
        tests/test_incoming_operation.cpp
        tests/test_outgoing_operation.cpp
        tests/test_logger.cpp
        tests/test_order_calculator.cpp
        tests/test_report_generator.cpp
        tests/test_strategy.cpp
        tests/test_scenarios.cpp
    )
    
    set(MISSING_TESTS "")
    foreach(TEST_FILE ${TEST_SOURCES})
        if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${TEST_FILE})
            message(WARNING "Test file not found: ${TEST_FILE}")
            list(APPEND MISSING_TESTS ${TEST_FILE})
        endif()
    endforeach()
    
    if(MISSING_TESTS)
        message(FATAL_ERROR "Missing test files: ${MISSING_TESTS}")
    endif()
    
    add_executable(WarehouseTests ${TEST_SOURCES})
    
    target_link_libraries(WarehouseTests 
        WarehouseLib
        Catch2::Catch2WithMain
    )
    
    target_include_directories(WarehouseTests PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    add_test(NAME WarehouseTests COMMAND WarehouseTests)
endif()