#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <exception>
#include <iostream>
#include <cstdlib>
#include <cstring>

using namespace std;

class Calculator
{
public:
    Calculator();
    double calc(const char* str); //throw(runtime_error);



    bool openParenthesis(int index = 0);

    /*!
     * \brief doOperation  выполняет операцию описанную в строке. Поддерживаемые операции: +, -, *, /, ^
     * \param str  строк с операции. Ожинается строка с двумя числами, операцией и пробелами.
     * Для корректной работы пробелы должны бтыть только между числами и операцией.
     * \return  результат выполнения операции
     */
    double doOperation(const char *str);

    char* searchOperation(const char *str);

    char* doubleToString(double num);

private:
    char* _str = nullptr;
    double _result = 0;

    double
        d1 = 0,
        d2 = 0;

    double stringToDouble(const char* str);

    /*!
     * \brief splitChar  разбивает сроку на два числа. Числа передаются в переменные класса d1 и d2
     * \param str  строка для преобразования
     * \param i номер символа по которуму происходит деление. Сам символ удаляется
     */
    void splitChar(const char *str, int i);

    /*!
     * \brief charIsDigit  проверка того что символ является числом
     * \param sym  проверяемый символ
     * \return  true - число, false - что-то иное
     */
    bool charIsDigit(char sym);
};

#endif // CALCULATOR_H
