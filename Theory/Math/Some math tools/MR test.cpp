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

int randomabint(int a, int b) { 
    return a + rand() % (b - a + 1); 
}

bool MR(int n) {
    for (int test = 0; test < 5; ++test) {
        int a = randomabint(2, n - 2);
        int s = 0;
        int d = n - 1;
        while (d % 2 == 0) {
            s += 1;
            d /= 2;
        }
        int x = Fast_power_mod(a, d, n);
        if (x != 1 && x != n - 1) {
            int F = 0;
            for (int i = 0; i < s - 1; ++i) {
                x = (x * x) % n;
                if (x == n - 1) {
                    F = 1;
                    break;
                }
            }
            if (F == 0) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    if (MR(n)) {
        cout << n << " is probably prime.\n";
    }
    else {
        cout << n << " is composite.\n";
    }

    return 0;
}
