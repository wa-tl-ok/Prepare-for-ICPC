//https://informatics.msk.ru/mod/statements/view.php?id=33342&chapterid=101#1

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

vector<int> Deliteli;
vector<ll> Pref_Hash(100005);
vector<ll> Step(100005);
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

    Step[0] = 1;
    for (int i = 1; i < 100005; i++) {
        Step[i] = (Step[i - 1] * 53) % mod;
    }
    Pref_Hash.resize((int)S.size());
    if (Pref_Hash[0] >= 'A' && Pref_Hash[0] <= 'Z') {
        Pref_Hash[0] = S[0] - 'A' + 27;
    }
    else {
        Pref_Hash[0] = S[0] - 'a' + 1;
    }
    for (int i = 1; i < (int)S.size(); ++i) {
        if (Pref_Hash[i] >= 'A' && Pref_Hash[i] <= 'Z') {
            Pref_Hash[i] = (Pref_Hash[i - 1] + ((S[i] - 'A' + 27) * Step[i]) % mod) % mod;
        }
        else {
            Pref_Hash[i] = (Pref_Hash[i - 1] + ((S[i] - 'a' + 1) * Step[i]) % mod) % mod;
        }
    }
    int l, r;
    for (int i = 1; i <= n; ++i) {
        int sz = i;
        bool flag = true;
        ll HASH = Take_Hash(0, sz - 1);
        for (l = 0; l < (int)S.size(); l += sz) {
            r = l + sz - 1;
            if (r >= n) {
                r = n - 1;
                if (Take_Hash(l, r) != Take_Hash(0, r - l)) {
                    flag = false;
                }
                break;
            }
            else {
                if (HASH != Take_Hash(l, r)) {
                    flag = false;
                }
            }
        }
        if (flag == true) {
            cout << sz;
            return 0;
        }
    }
}
