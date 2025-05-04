#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <cmath>
#include <unordered_map>

using namespace std;

const unordered_map<string, int> OPERATOR_PRIORITY{ {"+", 1}, {"-", 1}, {"*", 2}, {"/", 2}, {"^", 3} };

vector<string> static Vector(const string& input) {
    vector<string> vec;
    string current;

    for (char ch : input) {
        if (isspace(ch)) {
            if (!current.empty()) {
                vec.push_back(current);
                current.clear();
            }
            continue;
        }

        if (isalnum(ch)) {
            current += ch;
        }
        else {
            if (!current.empty()) {
                vec.push_back(current);
                current.clear();
            }
            vec.push_back(string(1, ch));
        }
    }

    if (!current.empty()) {
        vec.push_back(current);
    }

    return vec;
}

string static Postfix(const string& expression) {
    vector<string> Polynome = Vector(expression);
    vector<string> Output;
    stack<string> Operations;

    for (const auto& part : Polynome) {
        if (isalnum(part.front())) Output.push_back(part);

        else if (part == "(") Operations.push(part);
        
        else if (part == ")") {
            while (!Operations.empty() && Operations.top() != "(") {
                Output.push_back(Operations.top());
                Operations.pop();
            }
            Operations.pop();
        }
        else {
            while (!Operations.empty() && Operations.top() != "(" &&
                OPERATOR_PRIORITY.at(Operations.top()) >= OPERATOR_PRIORITY.at(part)) {
                Output.push_back(Operations.top());
                Operations.pop();
            }
            Operations.push(part);
        }
    }

    while (!Operations.empty()) {
        Output.push_back(Operations.top());
        Operations.pop();
    }

    ostringstream oss;
    for (size_t i = 0; i < Output.size(); ++i) {
        if (i > 0) oss << " ";
        oss << Output[i];
    }
    return oss.str();
}

double solvePostfix(const string& postfix, const unordered_map<string, double>& vars) {
    stack<double> stack;
    istringstream iss(postfix);
    string op;

    while (iss >> op) {
        if (isdigit(op.front())) {
            stack.push(stod(op));
        }
        else if (isalpha(op.front())) {
            if (!vars.count(op)) {
                throw invalid_argument("No matching variable found: " + op);
            }
            stack.push(vars.at(op));
        }
        else {
            if (stack.size() < 2) {
                throw invalid_argument("Invalid expression");
            }

            double b = stack.top(); stack.pop();
            double a = stack.top(); stack.pop();

            if (op == "+") stack.push(a + b);
            else if (op == "-") stack.push(a - b);
            else if (op == "*") stack.push(a * b);
            else if (op == "/") stack.push(a / b);
            else if (op == "^") stack.push(pow(a, b));
            else throw invalid_argument("No matching operator found: " + op);
        }
    }

    if (stack.size() != 1) {
        throw invalid_argument("Invalid expression");
    }
    return stack.top();
}

double solveExp(const string& expr, const unordered_map<string, double>& vars) {
    if (expr.find_first_of("()") != string::npos) {
        return solvePostfix(Postfix(expr), vars);
    }
    return solvePostfix(expr, vars);
}

int main() {
    string expression = "(3+4*x)*5-(2^3)";
    unordered_map<string, double> variables = { {"x", 5} };

    string postfix = Postfix(expression);
    cout << "Infix: " << expression << "\nPostfix: " << postfix << endl;

    cout << "Result: " << solveExp(expression, variables) << endl;
    cout << "Postfix Result: " << solveExp(postfix, variables) << endl;

    return 0;
}