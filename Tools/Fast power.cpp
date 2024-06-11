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
#include <random>

using namespace std;

int Fast_power_mod(int a, int n, int mod) {
    if (n == 0) { 
        return 1; 
    }

    int result = 1; 
    int base = a;

    while (n > 0) {
        if (n % 2 == 1) { 
            result = (result * base) % mod; 
        }

        base = (base * base) % mod; 
        n = n / 2;
    }

    return result % mod;
}

int Fast_power(int a, int n) {
    if (n == 0) { 
        return 1; 
    }

    int result = 1; 
    int base = a;

    while (n > 0) {
        if (n % 2 == 1) { 
            result = result * base; 
        }

        base = base * base; 
        n = n / 2;
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}
