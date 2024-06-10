//https://informatics.msk.ru/mod/statements/view.php?chapterid=2786#1

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

struct DSU {
    vector<int> head;
    vector<int> rang;

    DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }

        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }
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

        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<string> ANS;

    struct Trio {
        string T;
        int u;
        int v;
    };

    int n, m, k; cin >> n >> m >> k;
    vector<vector<int>> G(n);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;

        --u;
        --v;

        G[u].push_back(v);
        G[v].push_back(u);
    }

    vector<Trio> Go;

    for (int i = 0; i < k; i++) {
        string Type; int u, v; cin >> Type >> u >> v;
        
        Go.push_back({ Type, u - 1, v - 1 });
    }

    reverse(Go.begin(), Go.end());

    DSU dsu(n);

    for (int i = 0; i < k; i++) {
        string Type; int u, v;

        Type = Go[i].T;
        u = Go[i].u;
        v = Go[i].v;

        if (Type == "cut") {
            dsu.Union(u, v);
        }
        else {
            if (dsu.Find(u) == dsu.Find(v)) {
                ANS.push_back("YES");
            }
            else {
                ANS.push_back("NO");
            }
        }
    }

    reverse(ANS.begin(), ANS.end());

    for (auto q : ANS) {
        cout << q << "\n";
    }

    return 0;
}
