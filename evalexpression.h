#ifndef EVALEXPRESSION_H
#define EVALEXPRESSION_H
#include<cstdlib>
#include<stdexcept>

inline double evalPlusMinus(const char*&expression);
inline double evalMulDiv(const char*&expression);
inline double evalPrefixAndBracket(const char*&expression)
{
    while(isspace(*expression))
        ++expression;
    switch(*expression)
    {
    case'0':case'1':case'2':case'3':case'4':case'5':case'6':case'7':case'8':case'9':
        return strtod(expression,(char**)&expression);
    case'-':
        return -evalPrefixAndBracket(++expression);
    case'+':
        return evalPrefixAndBracket(++expression);
    case'(':
    {
        double res=evalPlusMinus(++expression);
        if(*expression++==')')
            return res;
    }
    default:
        throw std::runtime_error("Bad expression");
    }
}

inline double evalMulDiv(const char *&expression)
{
    double res=evalPrefixAndBracket(expression);
    while(true)
    {
        while(isspace(*expression))
            ++expression;
        switch(*expression)
        {
        case 0:
            return res;
        case'*':
            res*=evalPrefixAndBracket(++expression);
            break;
        case'/':
            res/=evalPrefixAndBracket(++expression);
            break;
        default:
            return res;
        }
    }
}

inline double evalPlusMinus(const char *&expression)
{
    double res=evalMulDiv(expression);
    while(true)
    {
        while(isspace(*expression))
            ++expression;
        switch(*expression)
        {
        case 0:
            return res;
        case'+':
            res+=evalMulDiv(++expression);
            break;
        case'-':
            res-=evalMulDiv(++expression);
            break;
        default:
            return res;
        }
    }
}

inline double evalExpression(const char *expression)
{
    const double res=evalPlusMinus(expression);
    while(isspace(*expression))
        ++expression;
    if(*expression)
        throw std::runtime_error("Bad expression");
    return res;
}
#endif // EVALEXPRESSION_H
