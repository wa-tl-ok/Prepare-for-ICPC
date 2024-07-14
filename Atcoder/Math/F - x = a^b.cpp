//https://atcoder.jp/contests/abc361/tasks/abc361_f

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

bool Check(long long x) {
    long long l = 0;
    long long r = 1000000001;

    while (l + 1 != r) {
        long long t = (l + r) / 2;
        if (t * t > x) { 
            r = t; 
        }
        else if (t * t < x) { 
            l = t;
        }
        else {
            return true;
        }
    }

    return false;
}

long long safe_pow(long long a, long long b) {
    long long p = 1;

    for (long long i = 0; i < b; i++) {
        double q = p;
        q *= a;

        if (q > 2e18) { 
            return 2e18; 
        }

        p *= a;
    }

    return p;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n; cin >> n;
    set<long long> ans_set;

    for (int a = 2; a <= 1000000; a++) {
        long long p = a;
        long long s = 3;
        
        while (safe_pow(p, s) <= n) {

            if (Check(safe_pow(p, s)) == false) {
                ans_set.insert(safe_pow(p, s));
            }

            s += 1;
        }
    }

    long long l = 1;
    long long r = 1000000001;

    while (l + 1 != r) {
        long long m = (l + r) / 2;

        if (m * m > n) {
            r = m;
        }
        else {
            l = m;
        }
    }

    long long ans = (long long)ans_set.size() + l;

    cout << ans;

    return 0;
}
