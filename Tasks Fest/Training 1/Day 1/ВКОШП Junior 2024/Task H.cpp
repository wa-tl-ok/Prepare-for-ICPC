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

#define int long long

vector<int> step1;
vector<int> step2;

int mod1 = 1200720071;
int mod2 = 1e9 + 7;

int HASH1(string s) {
    int n = s.size();
    int h = 0;

    for (int i = 0; i < n; i++) {
        h += (s[i] - 'a' + 1) * step1[i];
        h %= mod1;
    }

    return h;
}

int HASH2(string s) {
    int n = s.size();
    int h = 0;

    for (int i = 0; i < n; i++) {
        h += (s[i] - 'a' + 1) * step2[i];
        h %= mod2;
    }

    return h;
}

pair<int, int> HASH(string s) {
    return { HASH1(s), HASH2(s) };
}

void Solve() {
    int n, m; cin >> n >> m;

    vector<pair<int, string>> P;
    set<pair<int, int>> NEED;
    map<pair<int, int>, int> M;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        NEED.insert(HASH(s));
    }

    int LEN = 0;

    for (int i = 0; i < m; i++) {
        string s; cin >> s;

        M[HASH(s)] += 1;
        P.push_back({ s.size(), s });

        LEN += s.size();
    }

    int LIM; cin >> LIM;

    if (LEN <= LIM) {
        cout << 0;
        return;
    }

    int ERASE = LEN - LIM;
    int K = 0;

    sort(P.begin(), P.end());
    reverse(P.begin(), P.end());

    for (int i = 0; i < m; i++) {
        if (NEED.find(HASH(P[i].second)) == NEED.end()) {
            ERASE -= P[i].first;
            ++K;

            if (ERASE <= 0) {
                cout << K;
                return;
            }
        }
        else {
            if (M[HASH(P[i].second)] > 1) {
                ERASE -= P[i].first;
                ++K;

                if (ERASE <= 0) {
                    cout << K;
                    return;
                }

                --M[HASH(P[i].second)];
            }
        }
    }

    cout << -1;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    step1.resize(250000);
    step1[0] = 1;
    for (int i = 1; i < 250000; i++) {
        step1[i] = step1[i - 1] * 57 % mod1;
    }

    step2.resize(250000);
    step2[0] = 1;
    for (int i = 1; i < 250000; i++) {
        step2[i] = step2[i - 1] * 37 % mod2;
    }

    int multitest = false;
    if (multitest == true) {
        int ctt; cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }
    }
    else {
        Solve();
    }

    return 0;
}
