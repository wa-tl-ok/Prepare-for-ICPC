#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>

using namespace std;

string Number_system(int number, int from_base, int to_base, bool upper = false) {
    string digits = "0123456789abcdefghijklmnopqrstuvwxyz";
    if (to_base > digits.length()) {
        return "";
    }
    else {
        string result = "";
        while (number > 0) {
            result = digits[number % to_base] + result;
            number /= to_base;
        }
        if (upper) {
            for (char& c : result) {
                c = toupper(c);
            }
        }
        return result;
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int number = 31;
    int from_base = 10;
    int to_base = 2;

    cout << Number_system(number, from_base, to_base);

    return 0;
}
