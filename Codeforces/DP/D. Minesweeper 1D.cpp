//https://codeforces.com/contest/404/problem/D

#include <iostream> 
#include <iomanip> 
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

const long long mod = 1000000007;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s; cin >> s;
    long long n = s.size();

    vector<vector<long long>> DP(n + 1);
    for (int i = 0; i < (int)DP.size(); i++) {
        DP[i].resize(5);
    }

    s = "#" + s;

    if (s[1] == '0') {
        DP[1][0] = 1;
    }
    else if (s[1] == '1') {
        DP[1][2] = 1;
    }
    else if (s[1] == '2' || s[n] == '2') {
        cout << 0;
        return 0;
    }
    else if (s[1] == '*') {
        DP[1][4] = 1;
    }
    else {
        DP[1][0] = 1;
        DP[1][2] = 1;
        DP[1][4] = 1;
    }

    for (int i = 2; i <= n; i++) {
        if (s[i] == '0') {
            DP[i][0] = (DP[i - 1][0] + DP[i - 1][1]) % mod;
        }
        if (s[i] == '1') {
            DP[i][1] = DP[i - 1][4];
            DP[i][2] = (DP[i - 1][0] + DP[i - 1][1]) % mod;
        }
        if (s[i] == '2') {
            DP[i][3] = DP[i - 1][4];
        }
        if (s[i] == '*') {
            DP[i][4] = (DP[i - 1][2] + DP[i - 1][3] + DP[i - 1][4]) % mod;
        }
        if (s[i] == '?') {
            DP[i][0] = (DP[i - 1][0] + DP[i - 1][1]) % mod;

            DP[i][1] = DP[i - 1][4];
            DP[i][2] = (DP[i - 1][0] + DP[i - 1][1]) % mod;

            DP[i][3] = DP[i - 1][4];

            DP[i][4] = (DP[i - 1][2] + DP[i - 1][3] + DP[i - 1][4]) % mod;
        }
    }

    cout << (DP[DP.size() - 1][0] + DP[DP.size() - 1][1] + DP[DP.size() - 1][4]) % mod;

    return 0;
}
