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

int mergeinverse(vector <int>& a) {
    int inv_count = 0;
    if (a.size() > 1) {
        int mid = a.size() / 2;
        vector<int> left(a.begin(), a.begin() + mid);
        vector<int> right(a.begin() + mid, a.end());
        inv_count += mergeinverse(left);
        inv_count += mergeinverse(right);
        int i = 0, j = 0, k = 0;
        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                a[k] = left[i];
                i++;
            }
            else {
                a[k] = right[j];
                j++;
                inv_count += left.size() - i;
            }
            k++;
        }
        while (i < left.size()) {
            a[k] = left[i];
            i++;
            k++;
        }
        while (j < right.size()) {
            a[k] = right[j];
            j++;
            k++;
        }
    }
    return inv_count;
}

void Solve() {
    string s; cin >> s;

    int A = 0, N = 0, T = 0, O = 0;
    for (char c : s) {
        if (c == 'A') { A++; }
        else if (c == 'N') { N++; }
        else if (c == 'T') { T++; }
        else { O++; }
    }

    map<char, int> K;
    K['A'] = A;
    K['N'] = N;
    K['T'] = T;
    K['O'] = O;

    int ans_num = -1;
    string ans_str = "";

    vector<string> perms = {
        "ANTO", "ANOT", "ATNO", "ATON", "AONT", "AOTN",
        "NATO", "NAOT", "NTAO", "NTOA", "NOAT", "NOTA",
        "TANO", "TAON", "TNAO", "TNOA", "TOAN", "TONA",
        "OANT", "OATN", "ONAT", "ONTA", "OTAN", "OTNA"
    };

    for (int i = 0; i < 24; i++) {
        string p = perms[i];

        map<char, int> mp;
        for (int j = 0; j < 4; j++) {
            mp[p[j]] = j;
        }

        vector<int> a;
        for (int j = 0; j < s.size(); j++) {
            a.push_back(mp[s[j]]);
        }

        int new_ans_num = mergeinverse(a);

        if (new_ans_num > ans_num) {
            ans_num = new_ans_num;
            ans_str = "";
            for (int j = 0; j < 4; j++) {
                for (int k = 0; k < K[p[j]]; k++) {
                    ans_str += p[j];
                }
            }
        }
    }

    cout << ans_str << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int multitest = true;
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
