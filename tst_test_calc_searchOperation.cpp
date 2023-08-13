
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "src/calculator.h"

using namespace testing;

struct TestData_2
{
    char* expres;
    char* res;
};

class TestCalculator_2 : public ::TestWithParam <TestData_2>
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


TEST_P(TestCalculator_2, searchOperation)
{
    TestData_2 Data = GetParam();
    char* work_res = calc->searchOperation(Data.expres);
    int res = strcmp (work_res, Data.res);

    EXPECT_EQ(res, 0) << "\nData.expres '" << Data.expres
                      << "'\nwork_res '" << work_res
                      << "'\nData.res '" << Data.res
                      << "'\nres " << res
                      << "\n";

    std::cout << "\n";
}


TestData_2 DataTest2[] = {

    ///  Тесты на возведение в степень
    {" 2.0 ^2. ", "2.0 ^2." }, // 0
    {"33 - 1.0^2.", "1.0^2." },        //  1
    {"33 - 1.0^2.3 + 22 ", "1.0^2.3" },  //  2
    {"33-1.0 ^2.+11", "1.0 ^2." },        //  3
    {"33 * 1.^2.", "1.^2." },     //  4
    {"3^3 - 1.0^2.", "3^3" },         //  5

    ///  Тесты на умножение
    {"2. + 1.0*1.", "1.0*1."},  //  6
    {"  4. * 1.0 ", "4. * 1.0"},  //  7
    {"55-12. *10.0", "12. *10.0"},   //  8
    {"22 + 10.0 *1. - 55.0 * 6", "10.0 *1."},  //  9
    {"4.*1.0  +10.5 + 44.", "4.*1.0"},   //  10
    {"12.0* 10.0", "12.0* 10.0"},        //  11

    ///  Тесты на деление
    {"  1.0 /1.", "1.0 /1."}, // 12
    {"55. + 4./0.5", "4./0.5"},
    {"12.0/ 10.0 + 22.55 - 2254.", "12.0/ 10.0"},
    {"10.0 / 0.1", "10.0 / 0.1"},
    {"456454. + 4./2.0 - 555. + 55", "4./2.0"},
    {"12./100.", "12./100."},

    ///  Тесты на работу со сложением
    {"4.+1.0  ", "4.+1.0"},   //  18
    {" 12.0+10.0 + 1.", "12.0+10.0"},
    {"  10.0 +1. ", "10.0 +1."},
    {"55 - 4.+1.0  + 456.", "4.+1.0"},
    {"12.0 + 10.0", "12.0 + 10.0"},

    ///  Тесты на вычитание
    {"   1.0-1.", "1.0-1."}, // 23
    {"4.-1.0   ", "4.-1.0"},
    {"12.0 -10.0  ", "12.0 -10.0"},
    {"10.0 -1. - 5.", "10.0 -1."},
    {"   4.-1.0 ", "4.-1.0"},
    {"12.0 - 10.0", "12.0 - 10.0"}

    };

INSTANTIATE_TEST_SUITE_P(Calculator2,
                         TestCalculator_2,
                         ValuesIn(DataTest2));

