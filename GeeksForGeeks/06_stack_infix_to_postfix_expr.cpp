#include <stack>
#include <iostream>
#include <cmath>

int precedenece(char c) {
    switch(c) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
        default:
            std::cout << "Error. Unknown operator: "<< c << std::endl;
            return -1;
    }
}

bool isOperand(char c) {
    if ( (c >= 'a' && c <= 'z') || 
        (c >= 'A' && c <= 'Z') || 
        (c >= '0' && c <= '9') ) return true;
    return false;
}

bool isOperator(char c) {
    switch(c) {
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return true;
    }
    return false;
}

bool hasHigherPriority(char op1, char op2) {
    return (precedenece(op1) >= precedenece(op2));
}

bool isOpenningParenthesis(char c) {
    switch (c) {
        case '(':
        case '[':
        case '{':
            return true;
    }
    return false;
}

bool isClosingParenthesis(char c) {
    switch (c) {
        case ')':
        case ']':
        case '}':
            return true;
    }
    return false;
}

std::string infixToPostfixSimple(std::string s) {
/* Assume the expression does not include any parentheses */
/* Input s: a*b - c*d */
/* From: https://www.youtube.com/watch?v=vq-nUF0G4fI */
    std::cout << "Infix expression: " << s << std::endl;
    std::stack<char> op;
    std::string result;
    /* Go through string */
    for (int i=0; i < s.length(); i++) {
        char c = s[i];
        if (isOperand(c)) {
            result += c;
        } else if (isOperator(c)) {
            while (!op.empty() && hasHigherPriority(op.top(), c)) {
                result += op.top();
                op.pop();
            }
            op.push(c);
        } else {
            std::cout << "Unexpected character. " << c << std::endl;
        }
    }
    while (!op.empty()) {
        result += op.top();
        op.pop();
    }
    std::cout << "Postfix expression: " << result << std::endl;
    return result;
}

bool isDummy(char c) {
    switch (c) {
        case ' ':
            return true;
    }
    return false;
}

std::string infixToPostfix(std::string s) {
/* Expression can include parentheses or brackets */
/* Input s: a*b - (c*d)/f */
/* From: https://www.youtube.com/watch?v=vq-nUF0G4fI */
    std::cout << "Infix expression: " << s << std::endl;
    std::stack<char> op;
    std::string result;
    /* Go through string */
    for (int i=0; i < s.length(); i++) {
        char c = s[i];
        if (isDummy(c)) continue;
        
        if (isOperand(c)) {
            result += c;
            
        } else if (isOperator(c)) {
            while (!op.empty() && !isOpenningParenthesis(op.top()) && hasHigherPriority(op.top(), c)) {
                result += op.top();
                op.pop();
            }
            op.push(c);
            
        } else if (isOpenningParenthesis(c)) {
            op.push(c);
            
        } else if (isClosingParenthesis(c)) {
            while (!op.empty() && !isOpenningParenthesis(op.top())) {
                result += op.top();
                op.pop();
            }
            op.pop();
        }
    }
    while (!op.empty()) {
        result += op.top();
        op.pop();
    }
    std::cout << "Postfix expression: " << result << std::endl;
    return result;
}

int compute(int first_num, int second_num, char op) {
    switch (op) {
        case '+':
            return (first_num + second_num);
        case '-':
            return (first_num - second_num);
        case '*': 
            return (first_num*second_num);
        case '/':
            return (first_num/second_num);
        case '^':
            return (std::pow(first_num, second_num));
        default:
            std::cout << "Error. Unknown operator" << std::endl;
            return -1;
    }
}

int evalPostfix(std::string s) {
/* Assumes numbers are only single digits */
    std::stack<int> res;
    for (int i=0; i < s.length(); i++) {
        char c = s[i];
        if (isDummy(c)) continue; /* goto next character in string */
        if (isOperand(c)) { /* should only be a single digit for now */
            int num = c - '0';
            res.push(num);
        } else if (isOperator(c)) { /* +, -, *, /, ^ */
            int second_num = res.top();
            res.pop();
            int first_num = res.top();
            res.pop();
            int val = compute(first_num, second_num, c); 
            res.push(val);
        } else {
            std::cout << "Invalid character in postfix." << std::endl;
            return -1;
        }
    }
    return res.top();
}

int main(int argc, char* argv[]) {

    //std::cout << infixToPostfixSimple("a^b-c*d+e") << std::endl;
    //std::cout << infixToPostfix("a*(b+c)") << std::endl;
    //std::cout << infixToPostfix("(a^2+3)*(b+c)-f*g^2") << std::endl;
    std::string postfix = infixToPostfix("1-2");
    std::cout << evalPostfix(postfix) << std::endl;
    return 0;
}
