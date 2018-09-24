#include <stack>
#include <iostream>

bool isBalancedParanthesis(std::string s) {
    std::stack<char> p;
    for (int i=0; i<s.length(); i++) {
        char c = s[i];
        if (c == '(') {
            p.push(c);
            continue;
        } else if (c == ')') {
            if (p.top() != '(') return false;
            p.pop();
        }
    } /* for i */
    if (!p.empty()) {
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    
    std::string s;
    std::cout << isBalancedParanthesis("128+(234)") << std::endl;
    std::cout << isBalancedParanthesis("128+(2)*((1-34)") << std::endl;
    
    return 0;
}