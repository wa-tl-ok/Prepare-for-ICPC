//https://codeforces.com/contest/958/problem/A2

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
#include <iomanip>

using namespace std;

#define int long long

class Hash {
public:
    Hash(string S) {
        s = S; Get_random();

        Step1.resize(MX);
        Step2.resize(MX);

        Step1[0] = Step2[0] = 1;

        for (int i = 1; i < MX; i++) {
            Step1[i] = (Step1[i - 1] * base1) % mod1;
            Step2[i] = (Step2[i - 1] * base2) % mod2;
        }

        PHash1.resize(S.size());
        PHash2.resize(S.size());

        PHash1[0] = (S[0] - 'a' + 1) % mod1;
        PHash2[0] = (S[0] - 'a' + 1) % mod2;

        for (int i = 1; i < (int)S.size(); ++i) {
            PHash1[i] = (PHash1[i - 1] + ((S[i] - 'a' + 1) * Step1[i]) % mod1) % mod1;
            PHash2[i] = (PHash2[i - 1] + ((S[i] - 'a' + 1) * Step2[i]) % mod2) % mod2;
        }

        reverse(S.begin(), S.end());

        RHash1.resize(S.size());
        RHash2.resize(S.size());

        RHash1[0] = (S[0] - 'a' + 1) % mod1;
        RHash2[0] = (S[0] - 'a' + 1) % mod2;

        for (int i = 1; i < (int)S.size(); ++i) {
            RHash1[i] = (RHash1[i - 1] + ((S[i] - 'a' + 1) * Step1[i]) % mod1) % mod1;
            RHash2[i] = (RHash2[i - 1] + ((S[i] - 'a' + 1) * Step2[i]) % mod2) % mod2;
        }

        reverse(S.begin(), S.end());
    }

    pair<int, int> P(int l, int r) {
        int a = Take_PHash1(l, r);
        int b = Take_PHash2(l, r);
        return { a, b };
    }

    pair<int, int> R(int l, int r) {
        int a = Take_RHash1(s.size() - r - 1, s.size() - l - 1);
        int b = Take_RHash2(s.size() - r - 1, s.size() - l - 1);
        return { a, b };
    }

    pair<int, int> SP(vector<pair<int, int>> v) {
        pair<int, int> ans = { 0, 0 };
        int len = 0;

        for (auto p : v) {
            int l = p.first;
            int r = p.second;

            ans.first = (ans.first + Take_PHash1(l, r, len)) % mod1;
            ans.second = (ans.second + Take_PHash2(l, r, len)) % mod2;

            len += (r - l + 1);
        }

        return ans;
    }

    pair<int, int> SR(vector<pair<int, int>> v) {
        reverse(v.begin(), v.end());

        pair<int, int> ans = { 0, 0 };
        int len = 0;

        for (auto p : v) {
            int l = p.first;
            int r = p.second;

            ans.first = (ans.first + Take_RHash1(s.size() - r - 1, s.size() - l - 1, len)) % mod1;
            ans.second = (ans.second + Take_RHash2(s.size() - r - 1, s.size() - l - 1, len)) % mod2;

            len += (r - l + 1);
        }

        return ans;
    }

    bool Check(int l, int r) {
        return P(l, r) == R(l, r);
    }

private:
    string s;
    int MX = 2000005;

    int mod1, base1, mod2, base2;

    vector<int> Step1;
    vector<int> Step2;

    vector<int> PHash1;
    vector<int> PHash2;

    vector<int> RHash1;
    vector<int> RHash2;

    void Get_random() {
        //std::random_device rd;
        //std::mt19937 eng(rd());

        //std::uniform_int_distribution<int> dist(0, 3);

        //int m1 = dist(eng);
        //int b1 = dist(eng);
        //int m2 = dist(eng);
        //int b2 = dist(eng);

        vector<int> mod = { 998244353, 1000000007, 1000000009, 1200720071 };
        vector<int> bases = { 61, 53, 31, 29 };

        mod1 = mod[0];
        mod2 = mod[1];
        base1 = bases[0];
        base2 = bases[1];
    }

    int Take_PHash1(int l, int r) {
        if (l == 0) {
            return ((PHash1[r] + mod1) % mod1 * Step1[s.size()]) % mod1;
        }
        return ((PHash1[r] - PHash1[l - 1] + mod1) % mod1 * Step1[s.size() - l]) % mod1;
    }

    int Take_PHash2(int l, int r) {
        if (l == 0) {
            return ((PHash2[r] + mod2) % mod2 * Step2[s.size()]) % mod2;
        }
        return ((PHash2[r] - PHash2[l - 1] + mod2) % mod2 * Step2[s.size() - l]) % mod2;
    }

    int Take_RHash1(int l, int r) {
        if (l == 0) {
            return ((RHash1[r] + mod1) % mod1 * Step1[s.size()]) % mod1;
        }
        return ((RHash1[r] - RHash1[l - 1] + mod1) % mod1 * Step1[s.size() - l]) % mod1;
    }

    int Take_RHash2(int l, int r) {
        if (l == 0) {
            return ((RHash2[r] + mod2) % mod2 * Step2[s.size()]) % mod2;
        }
        return ((RHash2[r] - RHash2[l - 1] + mod2) % mod2 * Step2[s.size() - l]) % mod2;
    }

    int Take_PHash1(int l, int r, int x) {
        if (l == 0) {
            return ((PHash1[r] + mod1) % mod1 * Step1[s.size() + x]) % mod1;
        }
        return ((PHash1[r] - PHash1[l - 1] + mod1) % mod1 * Step1[s.size() - l + x]) % mod1;
    }

    int Take_PHash2(int l, int r, int x) {
        if (l == 0) {
            return ((PHash2[r] + mod2) % mod2 * Step2[s.size() + x]) % mod2;
        }
        return ((PHash2[r] - PHash2[l - 1] + mod2) % mod2 * Step2[s.size() - l + x]) % mod2;
    }

    int Take_RHash1(int l, int r, int x) {
        if (l == 0) {
            return ((RHash1[r] + mod1) % mod1 * Step1[s.size() + x]) % mod1;
        }
        return ((RHash1[r] - RHash1[l - 1] + mod1) % mod1 * Step1[s.size() - l + x]) % mod1;
    }

    int Take_RHash2(int l, int r, int x) {
        if (l == 0) {
            return ((RHash2[r] + mod2) % mod2 * Step2[s.size() + x]) % mod2;
        }
        return ((RHash2[r] - RHash2[l - 1] + mod2) % mod2 * Step2[s.size() - l + x]) % mod2;
    }
};

void Solve() {
    int n, m; cin >> n >> m;
    int size = m * m;
    string s1 = "";
    for (int i = 0; i < n; i++) {
        string g; cin >> g;
        s1 += g;
    }
    string s2 = "";
    for (int i = 0; i < m; i++) {
        string g; cin >> g;
        s2 += g;
    }
    map<pair<int, int>, int> F;
    Hash h1(s1);
    for (int l = 0; l < n; l++) {
        int r = l + m - 1;
        if (r >= n) {
            continue;
        }
        int L = l * m;
        int R = L + m * m - 1;
        F[h1.P(L, R)] = l;
    }
    Hash h2(s2);
    for (int l = 0; l < n; l++) {
        if (l + m - 1 >= n) {
            continue;
        }
        vector<pair<int, int>> to;
        int now = l;
        while (now < n * m) {
            to.push_back({ now, now + m - 1 });
            now += n;
        }
        if (F.find(h2.SP(to)) != F.end()) {
            cout << F[h2.SP(to)] + 1 << ' ' << l + 1;
            return;
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

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
