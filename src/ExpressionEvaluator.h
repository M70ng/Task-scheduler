#ifndef EXPRESSIONEVALUATOR_H
#define EXPRESSIONEVALUATOR_H

#include "Stack.h"
#include <string>
#include <sstream>
#include <cctype>
#include <iostream>

class ExpressionEvaluator {
public:
    static string infixToPostfix(const string& infix);
    static double evaluatePostfix(const string& postfix);
};

#endif