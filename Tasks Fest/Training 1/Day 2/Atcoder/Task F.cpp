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

int Num(string S) {
    int ans = 0;

    for (int i = 0; i < (int)S.size(); i++) {
        if (S[i] == '?') {
            continue;
        }

        ans = ans * 10 + (int)(S[i] - '0');
    }

    return ans;
}

int Place(string S, int x) {
    string SX = (to_string)(x);
    int r = SX.size() - 1;

    for (int i = (int)S.size() - 1; i >= 0; i--) {
        if (r < 0) {
            break;
        }

        if (S[i] == '?') {
            S[i] = SX[r];
            r--;
        }
    }

    for (int i = 0; i < (int)S.size(); i++) {
        if (S[i] == '?') {
            S[i] = '0';
        }
    }

    return Num(S);
}

int Pow(int a, int n) {
    int ans = 1;

    for (int i = 0; i < n; i++) {
        ans *= a;
    }

    return ans;
}

char Start(string S) {
    for (int i = 0; i < (int)S.size(); i++) {
        if (S[i] != '?') {
            return S[i];
        }
    }
    return '?';
}

int Len(string S) {
    int ans = 0;
    for (int i = 0; i < S.size(); i++) {
        if (S[i] != '?') {
            ++ans;
        }
    }
    return ans;
}

int Find(string S, int k, int MX) {
    int l = 0;
    int r = Pow(10, 16 - Len(S)) + 1;

    while (l + 1 != r) {
        int m = (l + r) / 2;

        int p;
        if (Start(S) != '0') {
            p = Place(S, m - 1);
        }
        else {
            p = Place(S, m - 1 + Pow(10, k));
        }

        if (p > MX) {
            r = m;
        }
        else {
            l = m;
        }
    }

    return l;
}

int DO(int x, string s) {
    int len_x = (to_string)(x).size();
    int len_s = s.size();

    int ans = 0;
    for (int k = 0; k <= len_x - len_s; k++) {
        string S = "";

        for (int i = 0; i < 18; i++) {
            S += "?";
        }

        string ss = s;

        int p = 0;
        for (int i = (int)ss.size() - 1; i >= 0; i--) {
            S[S.size() - 1 - p - k] = ss[i];
            ++p;
        }

        ans += Find(S, k, x);
    }

    return ans;
}

vector<int> ANS;

void Solve() {
    string s; int l, r; cin >> s >> l >> r;
    ANS.push_back(DO(r, s) - DO(l - 1, s));
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
    if (multitest == true) {
        int ctt;
        cin >> ctt;

        for (int i = 0; i < ctt; i++) {
            Solve();
        }

        for (auto ans : ANS) {
            cout << ans << '\n';
        }
    }
    else {
        Solve();
    }

    return 0;
}
