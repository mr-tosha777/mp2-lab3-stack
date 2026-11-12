#include "poland.h"
#include <gtest/gtest.h>

TEST(PolishExpression, infix_to_postfix_simple)
{
    PolishExpression expr("2+3");
    EXPECT_EQ("23+", expr.GetPostfix());
}

TEST(PolishExpression, calculate_simple)
{
    PolishExpression expr("a+b");
    map<char, double> vals = { { 'a', 2 },{ 'b', 3 } };
    EXPECT_DOUBLE_EQ(5.0, expr.Calculate(vals));
}

TEST(PolishExpression, calculate_with_variables)
{
    PolishExpression expr("a+b*c");
    map<char, double> vals;
    vals['a'] = 2;
    vals['b'] = 3;
    vals['c'] = 4;
    EXPECT_DOUBLE_EQ(14.0, expr.Calculate(vals));
}

TEST(PolishExpression, division_by_zero_throws)
{
    PolishExpression expr("5/0");
    map<char, double> vals;
    ASSERT_ANY_THROW(expr.Calculate(vals));
}