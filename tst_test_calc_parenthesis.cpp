
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "src/calculator.h"

using namespace testing;

struct TestData_5
{
    char* expres;
    char* res;
};

class TestCalculator_5 : public ::TestWithParam <TestData_5>
{
protected:
    void SetUp()
    {
        calc = new Calculator();
    }

    void TearDown()
    {
        delete calc;
    }

    Calculator* calc = nullptr;
};


TEST_P(TestCalculator_5, parenthesis)
{
    TestData_5 Data = GetParam();
    char* work_res = calc->extractParenthesis(Data.expres);
    int res = strcmp (work_res, Data.res);

    EXPECT_EQ(res, 0) << "\nData.expres '" << Data.expres
                      << "'\nwork_res '" << work_res
                      << "'\nData.res '" << Data.res
                      << "'\nres " << res
                      << "\n";

    std::cout << "\n";
}


TestData_5 DataTest5[] = {

    ///  Тесты на открытие скобочек
    {"(1.)", "1." }, // 0
    {"(1. + 2.)", "1. + 2." }, // 1
    {"(4. - 1.0)", "4. - 1.0" }, // 2
    {"(2. - 1.0)", "2. - 1.0" }, // 3
    {"(1. * 2.)", "1. * 2." }, // 4
    {"(1. ^ 2.)", "1. ^ 2." }
    };

INSTANTIATE_TEST_SUITE_P(Calculator_5,
                         TestCalculator_5,
                         ValuesIn(DataTest5));

