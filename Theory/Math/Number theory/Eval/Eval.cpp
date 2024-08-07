#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <stack>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <functional>
#include <chrono>
#include <cassert>

using namespace std;

stack<int> values;
stack<char> operations;

void Check() {
    int r = values.top();
    values.pop();

    int l = values.top();
    values.pop();

    char c = operations.top();
    operations.pop();

    if (c == '+') values.push(l + r);
    if (c == '-') values.push(l - r);
    if (c == '/') values.push(l / r);
    if (c == '*') values.push(l * r);
}

int Priority(char c) {
    if (c == '+' || c == '-') {
        return 1;
    }
    if (c == '*' || c == '/') {
        return 2;
    }
    return 0;
}

int Eval(string s) {
    s = '(' + s + ')';
    for (char c : s)
        if ('0' <= c && c <= '9') {
            values.push(c - '0');
        }
        else if (c == '(') {
            operations.push(c);
        }
        else if (c == ')') {
            while (operations.top() != '(') {
                Check();
            }
            operations.pop();
        }
        else {
            while (operations.size() > 0 && Priority(operations.top()) >= Priority(c)) {
                Check();
            }
            operations.push(c);
        }
    return values.top();
}

int main() {
    string s = "2+2*2";
    cout << Eval(s) << '\n';
}
