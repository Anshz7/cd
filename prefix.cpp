#include <iostream>
#include <stack>
#include <algorithm>

using namespace std;

// Function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix to postfix notation
string infixToPostfix(string infix) {
    stack<char> s;
    string postfix = "";
    for (char c : infix) {
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            s.pop();
        } else {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

// Function to convert infix to prefix notation
string infixToPrefix(string infix) {
    reverse(infix.begin(), infix.end());
    for (char &c : infix) {
        if (c == '(') c = ')';
        else if (c == ')') c = '(';
    }
    string prefix = infixToPostfix(infix);
    reverse(prefix.begin(), prefix.end());
    return prefix;
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;
   
    string postfix = infixToPostfix(infix);
    string prefix = infixToPrefix(infix);
   
    cout << "Postfix Notation: " << postfix << endl;
    cout << "Prefix Notation: " << prefix << endl;
   
    return 0;
}

// Sample input
// (A+B)*C