//https://atcoder.jp/contests/arc180/tasks/arc180_a

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

const long long mod = 1e9 + 7;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    string s; cin >> s;
    s = s + s[s.size() - 1];

    long long ans = 1;

    vector<char> st;
    for (int i = 0; i <= n; i++) {
        if (st.size() != 0 && st[st.size() - 1] == s[i]) {
            ans = (ans * (((long long)st.size() + 1) / 2)) % mod;
            st.clear();
        }
        st.push_back(s[i]);
    }

    cout << ans;

    return 0;
}
