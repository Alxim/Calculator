﻿#include "calculator.h"
#include "math.h"


Calculator::Calculator()
{

}


double Calculator::calc(const char *str)// throw(runtime_error)
{
    char _str[256];
    strcpy(_str, str);

    char* search = extractParenthesis(_str);
    double res = 0;
    char* res_s,
        * r_search;
    int index, len_search;

    while(search != nullptr)
    {
        res = calc(search);

        if(strcmp(search, _str) == 0)
            return res;

        //  замена

        res_s = doubleToString(res);

        r_search = strstr(_str, search);
        index = (int)(r_search - _str);
        len_search = strlen(search);

        strcat(res_s, _str + index + len_search + 1);
        strcpy(_str + index - 1, res_s);

        search = extractParenthesis(_str);
    }


    search = searchOperation(_str);


    while(search != nullptr)
    {
        try {
            res = doOperation(search);
        }
        catch(runtime_error) {
            throw;
        }

        if(strcmp(search, _str) == 0)
            return res;

        //  замена

        res_s = doubleToString(res);

        r_search = strstr(_str, search);
        index = (int)(r_search - _str);
        len_search = strlen(search);

        strcat(res_s, _str + index + len_search);
        strcpy(_str + index, res_s);

        search = searchOperation(_str);
    }

    double result = 0;
    try {
        result = stringToDouble(_str);
    }
    catch(runtime_error) {
        throw;
    }

    return result;
}



char* Calculator::extractParenthesis(const char *str)
{
    int len_str = strlen(str);
    int paren_open = -1,
        paren_open_count = 0,
        paren_close = -1;

    for(int i = 0; i < len_str; i++)
    {
        if(str[i] == '(')
        {
            paren_open_count++;

            if(paren_open == -1)
            {
                paren_open = i;
                continue;
            }
        }

        if(str[i] == ')')
        {
            paren_open_count--;

            if(paren_open_count == 0)
            {
                paren_close = i;
                int paren_len = paren_close - paren_open - 1;

                char* temp = new char(paren_len);

                strncpy(temp, str + paren_open + 1, paren_len);
                temp[paren_len] = '\0';

                return temp;
            }
        }
    }

    return nullptr;
}


void Calculator::splitChar(const char *str, int i)
{
    int len = strlen (str);

    char *s1 = new char(i),
        *s2 = new char(len);

    strncpy(s1, str, i);
    s1[i-1] = '\0';
    strcpy(s2, str + i);

    try {
        d1 = stringToDouble(s1);
        d2 = stringToDouble(s2);
    }
    catch(runtime_error) {
        throw;
    }
    //    delete s1;
    //    delete s2;
}


double Calculator::doOperation(const char *str)
{
    //  Проверка наличния сложения
    char *r_search;

    r_search = strstr( str, "^" );
    if(r_search != nullptr)
    {
        int i_plus = (int)(r_search - str + 1);
        splitChar(str, i_plus);
        return pow(d1, d2);
    }

    r_search = strstr( str, "+" );
    if(r_search != nullptr)
    {
        int i_plus = (int)(r_search - str + 1);
        splitChar(str, i_plus);
        return d1 + d2;
    }

    r_search = strstr( str, "-" );
    if(r_search != nullptr)
    {
        int i_plus = (int)(r_search - str + 1);
        splitChar(str, i_plus);
        return d1 - d2;
    }

    r_search = strstr( str, "*" );
    if(r_search != nullptr)
    {
        int i_plus = (int)(r_search - str + 1);
        splitChar(str, i_plus);
        return d1 * d2;
    }

    r_search = strstr( str, "/" );
    if(r_search != nullptr)
    {
        int i_plus = (int)(r_search - str + 1);
        splitChar(str, i_plus);
        return d1 / d2;
    }

    double res = stringToDouble(str);
    return res;
}


char* Calculator::searchOperation(const char *str)
{
    char* r_search = strpbrk( str, "^*/+-" );

    if( r_search == nullptr)
        return r_search;


    //  Операции ( ), +, -, *, /, ^

    //  Первая по приоритету выполнения скобочки, но она обрабатывается в другом месте

    //  Возводение в степень

    r_search = strrchr( str, '^' );

    if(r_search == nullptr)
    {
        //  Умножение или деление
        r_search = strpbrk( str, "*/" );

        if(r_search == nullptr)
        {
            //  Сложение или вычитание
            r_search = strpbrk( str, "+-" );

            if(r_search == nullptr)
                return r_search;
        }
    }

    int len = strlen(str);
    int i_oper = (int)(r_search - str + 1);
    //  Поиск символов слева и справа

    //  Поиск символов справа. Допустимое значение пробелы, числа, точка числа '  555.777'
    bool first_space_go = true,
        first_dot_dont = true;

    int right_limit = -1;

    for(int i = i_oper; i < len; i++)
    {
        char sym = str[i];

        if(first_space_go)
        {
            if(sym != ' ')
                first_space_go = false;
            else
                continue;
        }

        if(charIsDigit(sym))
        {
            continue;
        }

        if(first_dot_dont && sym == '.')
        {
            first_dot_dont = false;
            continue;
        }

        right_limit = i;
        break;
    }

    if(right_limit == -1)
        right_limit = len;

    //  Поиск символов слева. Допустимое значение пробелы, числа, точка числа '  555.777'
    first_space_go = true;
    first_dot_dont = true;

    int left_limit = 0;

    for(int i = i_oper-2; i > -1; i--)
    {
        char sym = str[i];

        if(first_space_go)
        {
            if(sym != ' ')
                first_space_go = false;
            else
                continue;
        }

        if(charIsDigit(sym))
        {
            continue;
        }

        if(first_dot_dont && sym == '.')
        {
            first_dot_dont = true;
            continue;
        }

        left_limit = i + 1;
        break;
    }


    int len_new = right_limit - left_limit;
    char* str_op = new char(len);
    strncpy(str_op, str + left_limit, len_new);
    str_op[len_new] = '\0';

    return str_op;
}


double Calculator::stringToDouble(const char *str)
{
    int len = strlen(str);
    double res = 0,
        factor_whole = 10, // множитель целой части
        factor_fraction = 1; //  множитель дробной части


    for(int i = 0; i < len; i++)
    {
        char sym = str[i];

        if(sym == ' ')
            continue;

        if(sym == '.')
        {
            factor_whole = 1;
            factor_fraction = 10;
            continue;
        }

        if(!charIsDigit(sym))
            throw runtime_error("Error convert string to double");

        res = res * factor_whole + double(sym - '0') / factor_fraction;
    }

    return res;
}


bool Calculator::charIsDigit(char sym)
{
    return sym >= '0' && sym <= '9';
}


char* Calculator::doubleToString(double num)
{
    // 567.54564
    int num2 = num;
    char* result = new char(256);
    char temp[256];
    temp[0] = '\0';

    while( num2 != 0 )
    {
        char sym = num2%10 + '0';
        result[0] = sym;
        result[1] = '\0';

        strcat(result, temp);

        strcpy(temp, result);
        num2 = num2/10;
    }

    strcat(result, ".");

    num = num - int(num);
    int i = 0,
        i_null = 0;
    while( num > 0 && i < 11 )
    {
        num *= 10;
        int num_int = num;
        char sym = num_int + '0';
        temp[0] = sym;
        temp[1] = '\0';

        if(sym == '0')
            i_null++;
        else
            i_null = 0;

        strcat(result, temp);
        num = num - num_int;
        i++;
    }

    if(i_null != 0)
        result[strlen(result) - i_null] = '\0';

    return result;
}
