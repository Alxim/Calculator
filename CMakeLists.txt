cmake_minimum_required(VERSION 3.5)

project(test_expressionCalculation LANGUAGES CXX)

enable_testing()



find_package(Threads REQUIRED)

if ($ENV{GOOGLETEST_DIR})
    set(GOOGLETEST_DIR $ENV{GOOGLETEST_DIR})
else ()
    if (NOT ${PROJECT_SOURCE_DIR}/googletest-1.14.0 STREQUAL "")
        message(WARNING "Using googletest src dir specified at Qt Creator wizard")
    endif ()
    set(GOOGLETEST_DIR "${PROJECT_SOURCE_DIR}/googletest-1.14.0")
endif ()
if (EXISTS ${GOOGLETEST_DIR})
    set(GTestSrc ${GOOGLETEST_DIR}/googletest)
    set(GMockSrc ${GOOGLETEST_DIR}/googlemock)
elseif (UNIX AND EXISTS /usr/src/gtest)
    set(GTestSrc /usr/src/gtest)
    message(WARNING "Using gtest from system")
    if (EXISTS /usr/src/gmock)
        set(GMockSrc /usr/src/gmock)
    endif ()
else ()
    message( FATAL_ERROR "No googletest src dir found - set GOOGLETEST_DIR to enable!")
endif ()

set(GTestFiles ${GTestSrc}/src/gtest-all.cc)
set(GTestIncludes ${GTestSrc} ${GTestSrc}/include)
if (NOT ${GMockSrc} STREQUAL "")
    list(APPEND GTestFiles ${GMockSrc}/src/gmock-all.cc)
    list(APPEND GTestIncludes ${GMockSrc} ${GMockSrc}/include)
endif ()

include_directories(${GTestIncludes})


set(PROJECT_SOURCES
    src/calculator.cpp
    src/calculator.h
)

add_executable(test_expressionCalculation
    main.cpp
    tst_test_calc_operation.cpp
    ${PROJECT_SOURCES}
    ${GTestFiles}
    tst_test_calc_searchOperation.cpp
    tst_test_calc_double_to_string.cpp
    tst_test_calc_calc.cpp)

add_test(NAME test_expressionCalculation COMMAND test_expressionCalculation)
target_link_libraries(test_expressionCalculation PRIVATE Threads::Threads)




