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

struct DSU {
    vector<int> head;
    vector<int> rang;
    int size;

    DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }

        size = n;
    }

    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return head[x] = Find(head[x]);
    }

    bool Union(int x, int y) {
        x = Find(x);
        y = Find(y);

        if (x == y) {
            return false;
        }

        if (rang[x] > rang[y]) {
            swap(x, y);
        }

        head[x] = y;

        if (rang[x] == rang[y]) {
            ++rang[y];
        }

        --size;

        return true;
    }
};

int Count(string s, char c) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == c) {
            return 1;
        }
    }
    return 0;
}

void Solve() {
    int n; cin >> n;

    DSU dsu(n + 1);

    vector<string> v;
    for (int i = 0; i < n; i++) {
        string s; cin >> s;
        v.push_back(s);
    }

    vector<char> alh = {
        'a', 'b',
        'c', 'd',
        'e', 'f',
        'g', 'h',
        'i', 'j',
        'k', 'l',
        'm', 'n',
        'o', 'p',
        'q', 'r',
        's', 't',
        'u', 'v',
        'w', 'x',
        'y', 'z'
    };

    for (int i = 0; i < 26; i++) {
        vector<int> m;
        char c = alh[i];

        for (int j = 0; j < n; j++) {
            string s = v[j];

            if (Count(s, c) > 0) {
                m.push_back(j + 1);
            }
        }

        if (m.size() > 1) {
            for (int j = 0; j < m.size() - 1; j++) {
                dsu.Union(m[j], m[j + 1]);
            }
        }
    }

    cout << dsu.size - 1;
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
