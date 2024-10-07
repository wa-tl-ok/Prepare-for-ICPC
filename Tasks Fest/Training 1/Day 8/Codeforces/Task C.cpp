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

void Solve() {
    int n; cin >> n;
    string s; cin >> s;

    string s1 = "";
    string s2 = "";

    pair<int, int> b = { 0, 0 };
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            if (b.first == 0) {
                s1 += "(";
                s2 += "(";

                b.first += 1;
                b.second += 1;
            }
            else if (b.first == 1) {
                if (i != n - 1 && s[i + 1] == '0' && b.first == b.second) {
                    s1 += "(";
                    s2 += "(";

                    b.first += 1;
                    b.second += 1;
                }
                else {
                    s1 += ")";
                    s2 += ")";

                    b.first -= 1;
                    b.second -= 1;
                }
            }
            else {
                s1 += ")";
                s2 += ")";

                b.first -= 1;
                b.second -= 1;
            }
        }
        else {
            if (b.first == b.second) {
                if (b.first == 0) {
                    cout << "NO\n";
                    return;
                }
                else {
                    b.first -= 1;
                    b.second += 1;

                    s1 += ")";
                    s2 += "(";
                }
            }
            else {
                b.first += 1;
                b.second -= 1;

                s1 += "(";
                s2 += ")";
            }
        }
    }

    if (b.first == 0 && b.second == 0) {
        cout << "YES\n";
        cout << s1 << '\n';
        cout << s2 << '\n';
    }
    else {
        cout << "NO\n";
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
