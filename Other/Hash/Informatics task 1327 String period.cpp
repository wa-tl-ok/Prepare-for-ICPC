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

using ll = long long;
using str = string;

vector<int> Nums;
vector<ll> Pref_Hash(1000005);
vector<ll> Step(1000005);
const ll mod = 1e9 + 7;
int n;

ll Take_Hash(int l, int r) {
    if (l == 0) {
        return (((Pref_Hash[r] + mod) % mod) * Step[n - l]) % mod;
    }
    return (((Pref_Hash[r] - Pref_Hash[l - 1] + mod) % mod) * Step[n - l]) % mod;
}

int main() {
    str S; cin >> S;
    n = (int)S.size();
    for (int i = 1; i <= n; ++i) {
        if (n % i == 0) {
            Nums.push_back(i);
        }
    }
    Step[0] = 1;
    for (int i = 1; i < 1000005; i++) {
        Step[i] = (Step[i - 1] * 31) % mod;
    }
    Pref_Hash[0] = S[0] - 'a' + 1;
    for (int i = 1; i < n; i++) {
        Pref_Hash[i] = ((Step[i] * (S[i] - 'a' + 1)) % mod + Pref_Hash[i - 1]) % mod;
    }
    for (int i = 0; i < (int)Nums.size(); i++) {
        ll HASH = Take_Hash(0, Nums[i] - 1);
        int ans = n / Nums[i]; int l, r;
        bool Flag = true;
        for (l = 0; l < n; l += Nums[i]) {
            r = l + Nums[i] - 1;
            if (Take_Hash(l, r) != HASH) {
                Flag = false;
            }
        }
        if (Flag == true) {
            cout << ans;
            return 0;
        }
    }
}
