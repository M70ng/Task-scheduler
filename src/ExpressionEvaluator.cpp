#include "ExpressionEvaluator.h"
#include <cmath>

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/' || op == '%') return 2;  // ← % 追加
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '%';  // ← % 追加
}

string ExpressionEvaluator::infixToPostfix(const string& infix) {
    Stack<char> st;
    string output;

    // We need to handle multi-digit numbers and decimals as single tokens.
    for (size_t i = 0; i < infix.size(); ++i) {
        char c = infix[i];
        if (isspace(c)) continue;

        if (isdigit(c) || c == '.') {
            // read full number
            if (!output.empty() && !isspace(output.back())) output += ' ';
            size_t j = i;
            string num;
            while (j < infix.size() && (isdigit(infix[j]) || infix[j] == '.')) {
                num += infix[j];
                ++j;
            }
            output += num;
            i = j - 1;
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.isEmpty() && st.peek() != '(') {
                output += ' ';
                output += st.pop();
            }
            if (!st.isEmpty()) st.pop(); // remove '('
        } else if (isOperator(c)) {
            // While top of stack has operator of higher or equal precedence, pop it to output
            while (!st.isEmpty() && isOperator(st.peek()) && precedence(st.peek()) >= precedence(c)) {
                output += ' ';
                output += st.pop();
            }
            // push current operator onto stack (will be output later)
            st.push(c);
        }
    }

    while (!st.isEmpty()) {
        if (st.peek() != '(' && st.peek() != ')') {
            output += ' ';
            output += st.pop();
        } else {
            // discard any stray parentheses
            st.pop();
        }
    }

    return output;
}

double ExpressionEvaluator::evaluatePostfix(const string& postfix) {
    Stack<double> st;
    stringstream ss(postfix);
    string token;

    while (ss >> token) {
        // token may be a number (starting with digit or '.') or an operator
        if (isdigit(token[0]) || token[0] == '.') {
            try {
                st.push(stod(token));
            } catch (...) {
                cerr << "Invalid number token: " << token << endl;
                st.push(0);
            }
        } else {
            double b = st.pop();
            double a = st.pop();
            if (token == "+") st.push(a + b);
            else if (token == "-") st.push(a - b);
            else if (token == "*") st.push(a * b);
            else if (token == "/") st.push(a / b);
            else if (token == "%") st.push(fmod(a, b));
            }
        }

    return st.pop();
}
