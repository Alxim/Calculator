
#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "src/calculator.h"

using namespace testing;

struct TestData4
{
    char* expres;
    double res;
};

class TestCalculator_4 : public ::TestWithParam <TestData4>
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


TEST_P(TestCalculator_4, calc)
{
    TestData4 Data = GetParam();
    double work_res = calc->calc(Data.expres);

    EXPECT_EQ(work_res, Data.res)
        << "\nData.expres '" << Data.expres
        << "'\nwork_res '" << work_res
        << "'\nData.res '" << Data.res
        << "\n";
    std::cout << "\n";
}


TestData4 DataNum4[] = {
    ///  Тесты на преобразование простого числа
    {"1.0", 1.0 },  // 0
    {"1.0 ", 1.0 },
    {" 1.0", 1.0 },

    ///  Тесты на работу со сложением
    {"1.0+1.", 2.0 }, // 3
    {"4.+1.0", 5.0 },
    {"12.0+10.0", 22.0},
    {"10.0 +1.", 11.0},
    {"4.+1.0 ", 5.0},
    {"12.0 + 10.0", 22.0},

    ///  Тесты на вычитание
    {"1.0-1.", 0.0}, // 9
    {"4.-1.0", 3.0},
    {"12.0-10.0", 2.0},
    {"10.0 -1.", 9.0},
    {"4.-1.0 ", 3.0},
    {"12.0 - 10.0", 2.0},

    ///  Тесты на умножение
    {"1.0*1.", 1.0}, // 15
    {"4.*1.0", 4.0},
    {"12.0*10.0", 120.0},
    {"10.0 *1.", 10.0},
    {"4.*1.0 ", 4.0},
    {"12.0 * 10.0", 120.0},

    //  Тесты на деление
    {"1.0/1.", 1.0}, // 21
    {"4./0.5", 8.0},
    {"12.0/10.0", 1.2},
    {"10.0 /0.1", 100.0},
    {"4./2.0 ", 2.0},
    {"12.0 / 100.0", 0.12},

    ///  Тесты на возведение в степень
    {"1.0^1.", 1.0}, // 27
    {"4.^0.5", 2.0},
    {"10.0^12.0", 1'000'000'000'000.0},
    {"10.0 ^2.0", 100.0},
    {"4.^2.0 ", 16.0},
    {"12.0 ^ 2.0", 144.0},

    ///  Примеры смешанных действий
    {"2.0 ^ 2. + 5.", 9.0},   // 33
    {"2.0 / 2. + 5.", 6.0},
    {"2.0 - 2. + 5.", 5.0},
    {"2.0 ^ 2. * 5.", 20.0},

    ///  Задачка
    {".10", 0.1},   //  37
    {"(1.)", 1.0},
    {"2.0 ^ 2. ^ 3.0", 256.0},
    {"13. / 2.0", 6.5},
    {"((4. - 1.0) / ((2.) - 1.0))", 3}
};

INSTANTIATE_TEST_SUITE_P(Calculator_4,
                         TestCalculator_4,
                         ValuesIn(DataNum4));

