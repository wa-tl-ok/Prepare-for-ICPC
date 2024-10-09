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
    int n, m; cin >> n >> m;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }

    sort(b.begin(), b.end());
    reverse(b.begin(), b.end());

    int la = 0;
    int lb = 0;

    while (la < n || lb < m) {
        if (la == n) {
            cout << b[lb] << ' ';
            ++lb;
        }
        else if (lb == m) {
            cout << a[la] << ' ';
            ++la;
        }
        else {
            if (a[la] > b[lb]) {
                cout << a[la] << ' ';
                ++la;
            }
            else {
                cout << b[lb] << ' ';
                ++lb;
            }
        }
    }

    cout << endl;
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
