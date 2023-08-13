
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "src/calculator.h"

using namespace testing;

struct TestData3
{
    double expres;
    char* res;
};

class TestCalculator_3 : public ::TestWithParam <TestData3>
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


TEST_P(TestCalculator_3, doubleToString)
{
    TestData3 Data = GetParam();
    char* work_res = calc->doubleToString(Data.expres);

    int res = strcmp (work_res, Data.res);

    EXPECT_EQ(res, 0)
        << "\nData.expres '" << Data.expres
        << "'\nwork_res '" << work_res
        << "'\nData.res '" << Data.res
        << "'\nres " << res
        << "\n";
    std::cout << "\n";
}


TestData3 DataNum3[] = {
    //  Тесты на преобразование простого числа
    { 1.0 , "1." },  // 0
    { 55, "55." },
    { 875, "875." },
    { 875.2, "875.2" },
    { 875.2464564, "875.2464564" }
};

INSTANTIATE_TEST_SUITE_P(Calculator_3,
                         TestCalculator_3,
                         ValuesIn(DataNum3));

