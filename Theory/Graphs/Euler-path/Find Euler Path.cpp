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

bool Check(vector<int> &in, vector<int> &out, int n) {
    int counter1 = 0;
    int counter2 = 0;
    for (int v = 0; v < n; v++) {
        if (out[v] == in[v]) {
            
        }
        else if (out[v] > in[v]) {
            if (out[v] - in[v] != 1) {
                return false;
            }
            else {
                ++counter1;
            }
        }
        else if (in[v] > out[v]) {
            if (in[v] - out[v] != 1) {
                return false;
            }
            else {
                ++counter2;
            }
        }
    }
    if (counter1 == 0 && counter2 == 0) {
        return true;
    }
    if (counter1 == 1 && counter2 == 1) {
        return true;
    }
    return false;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    vector<int> ans;

    int n, m; cin >> n >> m;

    vector<multiset<int>> g(n);
    vector<int> in(n, 0);
    vector<int> out(n, 0);

    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;

        --u;
        --v;

        g[u].insert(v);

        ++in[v];
        ++out[u];
    }

    if (Check(in ,out, n) == false) {
        cout << "NO";
        return 0;
    }

    int start = -1;

    for (int v = 0; v < n; v++) {
        if (out[v] > in[v]) {
            start = v;
        }
    }

    if (start == -1) {
        for (int v = 0; v < n; v++) {
            if (g[v].size() > 0) {
                start = v;
            }
        }
    }

    stack<int> stack;
    stack.push(start);

    while (stack.size() > 0) {
        int last = stack.top();
        if (g[last].size() == 0) {
            stack.pop();
            ans.push_back(last);
        }
        else {
            int u = last;
            int v = *g[last].begin();

            g[u].erase(g[u].find(v));

            stack.push(v);
        }
    }

    reverse(ans.begin(), ans.end());

    string ANS = "YES";
    for (int v = 0; v < n; v++) {
        if (g[v].size() > 0) {
            ANS = "NO";
        }
    }

    if (ANS == "NO") {
        cout << ANS << endl;
    }
    else {
        cout << ANS << " : ";
        for (auto l : ans) {
            cout << l + 1 << ' ';
        }
    }

    return 0;
}
