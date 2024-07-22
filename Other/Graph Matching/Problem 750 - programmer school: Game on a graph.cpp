//https://acmp.ru/index.asp?main=task&id_task=750

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

vector<vector<int>> G;
vector<bool> DFS;

vector<int> px, py;
vector<bool> killed1, killed2;

bool dfs(int v) {
    DFS[v] = true;
    for (int u : G[v]) {
        if (killed2[u] == true) {
            continue;
        }

        if (py[u] == -1) {
            px[v] = u;
            py[u] = v;

            return true;
        }

        if (DFS[py[u]] == false && killed1[py[u]] == false) {
            if (dfs(py[u])) {
                px[v] = u;
                py[u] = v;

                return true;
            }
        }
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    freopen("INPUT.TXT", "r", stdin);
    freopen("OUTPUT.TXT", "w", stdout);

    int n1, n2, m; cin >> n1 >> n2 >> m;
    G.resize(n1);
    DFS.resize(n1);

    for (int i = 0; i < m; ++i) {
        int a, b; cin >> a >> b;

        --a;
        --b;

        G[a].push_back(b);
    }

    px.resize(n1, -1);
    py.resize(n2, -1);

    killed1.resize(n1, false);
    killed2.resize(n2, false);

    for (int u = 0; u < n1; ++u) {
        for (int j = 0; j < n1; j++) {
            DFS[j] = false;
        }

        dfs(u);
    }

    vector<char> ans1(n1);
    vector<char> ans2(n2);

    for (int u = 0; u < n1; ++u) {
        if (px[u] == -1) {
            ans1[u] = 'P';
        }
        else {
            py[px[u]] = -1;
            killed1[u] = true;

            for (int j = 0; j < n1; j++) {
                DFS[j] = false;
            }

            bool found = false;

            for (int v = 0; v < n1; ++v) {
                if (v != u && px[v] == -1 && DFS[v] == false && dfs(v) == true) {
                    found = true;
                    break;
                }
            }

            if (found == true) {
                ans1[u] = 'P';

                px[u] = -1;
                killed1[u] = false;
            }
            else {
                ans1[u] = 'N';

                py[px[u]] = u;
                killed1[u] = false;
            }
        }
    }

    for (int i = 0; i < n2; ++i) {
        if (py[i] == -1) {
            ans2[i] = 'P';
        }
        else {
            px[py[i]] = -1;
            killed2[i] = true;

            for (int j = 0; j < n1; j++) {
                DFS[j] = false;
            }

            bool found = false;

            for (int j = 0; j < n1; ++j) {
                if (px[j] == -1 && DFS[j] == false && dfs(j) == true) {
                    found = true;
                    break;
                }
            }

            if (found == true) {
                ans2[i] = 'P';
                py[i] = -1;
                killed2[i] = false;
            }
            else {
                ans2[i] = 'N';
                px[py[i]] = i;
                killed2[i] = false;
            }
        }
    }

    for (char c : ans1) {
        cout << c;
    }
    cout << endl;
    for (char c : ans2) {
        cout << c;
    }
    cout << endl;

    return 0;
}
