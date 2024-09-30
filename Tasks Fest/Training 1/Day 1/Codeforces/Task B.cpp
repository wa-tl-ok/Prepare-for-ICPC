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

string replace(string s, int pos, char c) {
    string ans = "";

    for (int i = 0; i < s.size(); i++) {
        if (i == pos) {
            ans += c;
        }
        else {
            ans += s[i];
        }
    }

    return ans;
}

void Solve() {
    int n; cin >> n;

    map<string, vector<int>> P;
    map<int, string> ans;
    set<string> ALL;

    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        P[s].push_back(i + 1);
        ALL.insert(s);
    }

    int K = 0;
    for (auto p : P) {
        string pa = p.first;
        vector<int> ind = p.second;
        K += ind.size() - 1;

        vector<char> c = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

        ans[ind[ind.size() - 1]] = pa;
        ind.pop_back();

        for (auto iiii : ind) {
            for (int i = 0; i < 10; i++) {
                string paa = replace(pa, 0, c[i]);

                if (ALL.find(paa) == ALL.end()) {
                    ALL.insert(paa);

                    ans[iiii] = paa;

                    break;
                }

                paa = replace(pa, 1, c[i]);

                if (ALL.find(paa) == ALL.end()) {
                    ALL.insert(paa);

                    ans[iiii] = paa;

                    break;
                }

                paa = replace(pa, 2, c[i]);

                if (ALL.find(paa) == ALL.end()) {
                    ALL.insert(paa);

                    ans[iiii] = paa;

                    break;
                }

                paa = replace(pa, 3, c[i]);

                if (ALL.find(paa) == ALL.end()) {
                    ALL.insert(paa);

                    ans[iiii] = paa;

                    break;
                }
            }
        }
    }

    cout << K << '\n';
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << '\n';
    }
}

int main() {
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
