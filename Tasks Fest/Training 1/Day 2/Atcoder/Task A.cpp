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

void Solve() {
    set<string> F;

    F.insert("and");
    F.insert("not");
    F.insert("the");
    F.insert("you");
    F.insert("that");

    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        if (F.find(s) != F.end()) {
            cout << "Yes";
            return;
        }
    }
    cout << "No";
}

int main() {
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
