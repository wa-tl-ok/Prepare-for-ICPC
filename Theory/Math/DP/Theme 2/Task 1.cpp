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

using namespace std;

class BigInt {
public:
    BigInt() : digits("0") {}

    BigInt(const string& num) : digits(num) {
        while (digits.size() > 1 && digits[0] == '0') {
            digits.erase(digits.begin());
        }
    }

    BigInt operator+(const BigInt& other) const {
        string result = "";
        int carry = 0;

        int i = digits.size() - 1;
        int j = other.digits.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int digit1;
            if (i >= 0) {
                digit1 = digits[i--] - '0';
            }
            else {
                digit1 = 0;
            }

            int digit2;
            if (j >= 0) {
                digit2 = other.digits[j--] - '0';
            }
            else {
                digit2 = 0;
            }

            int sum = digit1 + digit2 + carry;
            carry = sum / 10;
            result.push_back((sum % 10) + '0');
        }

        reverse(result.begin(), result.end());
        return BigInt(result);
    }

    friend ostream& operator<<(ostream& out, const BigInt& num);

private:
    string digits;
};

ostream& operator<<(ostream& out, const BigInt& num) {
    out << num.digits;
    return out;
}

BigInt a[105][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n;
    cin >> n;

    a[1][0] = BigInt("1");
    a[1][1] = BigInt("1");

    for (int i = 2; i <= 100; i++) {
        a[i][0] = a[i - 1][0] + a[i - 1][1];
        a[i][1] = a[i - 1][0];
    }

    cout << a[n][0] + a[n][1];

    return 0;
}
