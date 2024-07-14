//https://atcoder.jp/contests/abc361/tasks/abc361_d

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

vector<string> nodes; int SIZE;

void Form(string& s) {
    if (s.size() == SIZE) {
        nodes.push_back(s);
        return;
    }

    string s1 = s + "W";
    string s2 = s + "B";

    Form(s1);
    Form(s2);
}

const long long mod = 1e9 + 7;

long long Hash(string& s) {
    vector<long long> step(20);
    step[0] = 1;

    for (int i = 1; i < 20; ++i) {
        step[i] = step[i - 1] * 31;
        step[i] %= mod;
    }

    long long s_Hash = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        s_Hash += step[i] * (s[i] - 'A' + 1);
        s_Hash %= mod;
    }

    return s_Hash;
}

void Solve(int s, int f, vector<vector<int>>& G) {
    int n = G.size();
    vector<int> dist(n, -1);
    queue<int> q;

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : G[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    if (dist[f] != -1) {
        cout << dist[f] << endl;
    }
    else {
        cout << -1 << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    SIZE = n;

    string S; cin >> S;
    string T; cin >> T;
    string st = "";

    Form(st);

    int l = (int)nodes.size();
    vector<string> Nodes;

    for (int node = 0; node < l; node++) {
        string s = nodes[node];

        for (int i = 0; i < (int)s.size(); i++) {
            string new_s = "";

            for (int j = 0; j < i; j++) {
                new_s += s[j];
            }

            new_s += 'Z';
            new_s += 'Z';

            for (int j = i; j < (int)s.size(); j++) {
                new_s += s[j];
            }

            Nodes.push_back(new_s);
        }

        s += 'Z';
        s += 'Z';

        Nodes.push_back(s);
    }

    unordered_map<long long, int> Num;

    l = n + 2;
    n = (int)Nodes.size();
    vector<vector<int>> G(n);

    for (int i = 0; i < n; i++) {
        Num[Hash(Nodes[i])] = i;
    }

    for (int si = 0; si < n; si++) {
        string s = Nodes[si];

        long long u = Hash(s); long long v = -1;

        int idx = -1;
        
        for (int i = 0; i < l - 1; i++) {
            if (s[i] == 'Z' && s[i + 1] == 'Z') {
                idx = i;
                break;
            }
        }

        int idx1 = idx;
        int idx2 = idx + 1;

        for (int i = 0; i < l - 1; i++) {
            if (i != idx1 && i != idx2 && i + 1 != idx1 && i + 1 != idx2) {
                string t = s;

                int pos1, pos2;
                char Temp;

                pos1 = i;
                pos2 = idx1;

                Temp = t[pos1];
                t[pos1] = t[pos2];
                t[pos2] = Temp;

                pos1 = i + 1;
                pos2 = idx2;

                Temp = t[pos1];
                t[pos1] = t[pos2];
                t[pos2] = Temp;

                v = Hash(t);

                G[Num[u]].push_back(Num[v]);
            }
        }
    }

    S += 'Z';
    S += 'Z';

    T += 'Z';
    T += 'Z';

    int s = Num[Hash(S)];
    int f = Num[Hash(T)];

    Solve(s, f, G);

    return 0;
}
