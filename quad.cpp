#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

struct Quadruple {
    string op, arg1, arg2, res;
};

struct Triple {
    string op, arg1, arg2;
};

struct IndirectTriple {
    int index;
    Triple triple;
};

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

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

void generateIntermediateCode(string postfix) {
    stack<string> s;
    vector<Quadruple> quadruples;
    vector<Triple> triples;
    vector<IndirectTriple> indirectTriples;
    int tempCount = 1;

    for (char c : postfix) {
        if (isalnum(c)) {
            s.push(string(1, c));
        } else {
            string arg2 = s.top(); s.pop();
            string arg1 = s.top(); s.pop();
            string temp = "T" + to_string(tempCount++);

            quadruples.push_back({string(1, c), arg1, arg2, temp});
            triples.push_back({string(1, c), arg1, arg2});
            indirectTriples.push_back({(int)triples.size() - 1, triples.back()});

            s.push(temp);
        }
    }

    cout << "\nQuadruple Representation:\n";
    cout << "Op | Arg1 | Arg2 | Result\n";
    for (auto &q : quadruples) {
        cout << q.op << "  |  " << q.arg1 << "   |  " << q.arg2 << "   |  " << q.res << "\n";
    }

    cout << "\nTriple Representation:\n";
    cout << "Index | Op | Arg1 | Arg2\n";
    for (size_t i = 0; i < triples.size(); i++) {
        cout << i << "     | " << triples[i].op << "  | " << triples[i].arg1 << "   | " << triples[i].arg2 << "\n";
    }

    cout << "\nIndirect Triple Representation:\n";
    cout << "Index | Triple Index | Op | Arg1 | Arg2\n";
    for (auto &it : indirectTriples) {
        cout << it.index << "     | " << it.index << "            | " << it.triple.op << "  | " << it.triple.arg1 << "   | " << it.triple.arg2 << "\n";
    }
}

int main() {
    string infix;
    cout << "Enter an infix expression: ";
    cin >> infix;
   
    string postfix = infixToPostfix(infix);
    cout << "Postfix Notation: " << postfix << endl;
   
    generateIntermediateCode(postfix);
   
    return 0;
}

// sample input
// a=b+c-d