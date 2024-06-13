//https://codeforces.com/problemset/problem/1800/D

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

vector <ll> Step_1(200005);
vector <ll> Step_2(200005);
vector <ll> Pref_Hash_1(200005);
vector <ll> Pref_Hash_2(200005);

ll mod_1 = 1200720071;
ll mod_2 = 1e9 + 7;

str s;
int n;

int ans = 0;
vector<int> ANS;

ll Take_Hash_1(int l, int r) {
    if (l == 0) {
        return (((Pref_Hash_1[r] + mod_1) % mod_1) * Step_1[n - l]) % mod_1;
    }
    return (((Pref_Hash_1[r] - Pref_Hash_1[l - 1] + mod_1) % mod_1) * Step_1[n - l]) % mod_1;
}

ll Take_Hash_2(int l, int r) {
    if (l == 0) {
        return (((Pref_Hash_2[r] + mod_2) % mod_2) * Step_2[n - l]) % mod_2;
    }
    return (((Pref_Hash_2[r] - Pref_Hash_2[l - 1] + mod_2) % mod_2) * Step_2[n - l]) % mod_2;
}

ll h1(int l, int r) {
    return Take_Hash_1(l, r);
}

ll h2(int l, int r) {
    return Take_Hash_2(l, r);
}

ll merge_1(int ind1, int ind2) {
    if (ind1 == 0) {
        return h1(2, n - 1);
    }
    if (ind2 == n - 1) {
        return h1(0, n - 3);
    }
    return (h1(0, ind1 - 1) + h1(ind2 + 1, n - 1) * Step_1[ind1] % mod_1) % mod_1;
}

ll merge_2(int ind1, int ind2) {
    if (ind1 == 0) {
        return h2(2, n - 1);
    }
    if (ind2 == n - 1) {
        return h2(0, n - 3);
    }
    return (h2(0, ind1 - 1) + h2(ind2 + 1, n - 1) * Step_2[ind1] % mod_2) % mod_2;
}

void Solve() {
    cin >> n;
    cin >> s;

    map <pair<ll, ll>, bool> m;

    Pref_Hash_1.clear();
    Pref_Hash_1.resize(n);
    Pref_Hash_1[0] = s[0] - 'a' + 1;
    for (int i = 1; i < (int)s.size(); i++) {
        Pref_Hash_1[i] = (Pref_Hash_1[i - 1] + ((s[i] - 'a' + 1) * Step_1[i]) % mod_1) % mod_1;
    }

    Pref_Hash_2.clear();
    Pref_Hash_2.resize(n);
    Pref_Hash_2[0] = s[0] - 'a' + 1;
    for (int i = 1; i < (int)s.size(); i++) {
        Pref_Hash_2[i] = (Pref_Hash_2[i - 1] + ((s[i] - 'a' + 1) * Step_2[i]) % mod_2) % mod_2;
    }

    for (int i = 0; i < n - 1; i++) {
        int ind1 = i;
        int ind2 = i + 1;

        ll p1 = merge_1(ind1, ind2);
        ll p2 = merge_2(ind1, ind2);

        if (m[make_pair(p1, p2)] != true) {
            ++ans;
            m[make_pair(p1, p2)] = true;
        }
    }

    ANS.push_back(ans);
}

int main() {
    Step_1[0] = 1;
    for (int i = 1; i < 200005; i++) {
        Step_1[i] = (Step_1[i - 1] * 29) % mod_1;
    }

    Step_2[0] = 1;
    for (int i = 1; i < 200005; i++) {
        Step_2[i] = (Step_2[i - 1] * 31) % mod_2;
    }

    int test; cin >> test;

    for (int i = 0; i < test; ++i) {
        ans = 0;
        Solve();
    }

    for (int i = 0; i < (int)ANS.size(); i++) {
        cout << ANS[i] << endl;
    }

    return 0;
}
