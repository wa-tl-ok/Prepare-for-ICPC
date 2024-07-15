//https://informatics.msk.ru/mod/statements/view.php?chapterid=1791#1

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s; cin >> s; int n = (int)s.size();
    string t; cin >> t; int m = (int)t.size();

    vector<vector<int>> DP(n + 1);
    for (int i = 0; i < n + 1; i++) {
        DP[i].resize(m + 1);
    }

    for (int i = 0; i < n + 1; i++) {
        DP[i][0] = i;
    }

    for (int j = 0; j < m + 1; j++) {
        DP[0][j] = j;
    }

    for (int i = 1; i < n + 1; i++) {
        for (int j = 1; j < m + 1; j++) {
            int si = i - 1;
            int tj = j - 1;

            if (s[si] == t[tj]) {
                DP[i][j] = DP[i - 1][j - 1];
            }
            else {
                DP[i][j] = min({ DP[i - 1][j], DP[i][j - 1], DP[i - 1][j - 1] }) + 1;
            }
        }
    }

    cout << DP[n][m] << endl;

    return 0;
}
