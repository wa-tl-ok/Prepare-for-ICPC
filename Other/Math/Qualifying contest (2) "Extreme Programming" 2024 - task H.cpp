//https://contest.yandex.ru/contest/66914/problems/H/

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

#define int long long 

int ans1;
int ans2;

int mod = 1e9 + 7;
vector<int> F;

vector<int> P1;
vector<int> P2;
vector<int> P3;
vector<int> P4;

int Ans1(string s) {
    s = s + s[s.size() - 1];
    vector<char> st;
    int K = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        if (st.size() != 0 && st[st.size() - 1] == s[i]) {
            if (st.size() > 2) {
                if (st[0] == 'O' && st[st.size() - 1] == 'O') {
                    K += (st.size() - 2) / 2;
                }
                if (st[0] == 'O' && st[st.size() - 1] == 'L') {
                    K += (st.size() - 1) / 2;
                }
                if (st[0] == 'L' && st[st.size() - 1] == 'O') {
                    K += (st.size() - 1) / 2;
                }
                if (st[0] == 'L' && st[st.size() - 1] == 'L') {
                    K += (st.size()) / 2;
                }
            }
            st.clear();
        }
        st.push_back(s[i]);
    }
    return K;
}

int modInverse(int a, int m) {
    int m0 = m, y = 0, x = 1;
    if (m == 1) {
        return 0;
    }
    while (a > 1) {
        int q = a / m;
        int t = m;
        m = a % m, a = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0) {
        x += m0;
    }
    return x;
}

int R(string s) {
    s = s + s[s.size() - 1];
    vector<char> st;
    int K = 1;
    for (int i = 0; i < (int)s.size(); i++) {
        if (st.size() != 0 && st[st.size() - 1] == s[i]) {
            if (st.size() > 2) {
                if (st[0] == 'O' && st[st.size() - 1] == 'O') {
                    K *= P1[st.size()];
                    K %= mod;
                }
                if (st[0] == 'O' && st[st.size() - 1] == 'L') {
                    K *= P2[st.size()];
                    K %= mod;
                }
                if (st[0] == 'L' && st[st.size() - 1] == 'O') {
                    K *= P3[st.size()];
                    K %= mod;
                }
                if (st[0] == 'L' && st[st.size() - 1] == 'L') {
                    K *= P4[st.size()];
                    K %= mod;
                }
            }
            st.clear();
        }
        st.push_back(s[i]);
    }
    return K;
}

int Ans2(string s) {
    s = s + s[s.size() - 1];
    vector<char> st;
    vector<int> a;
    for (int i = 0; i < (int)s.size(); i++) {
        if (st.size() != 0 && st[st.size() - 1] == s[i]) {
            if (st.size() > 2) {
                if (st[0] == 'O' && st[st.size() - 1] == 'O') {
                    a.push_back(F[(st.size() - 2) / 2]);
                }
                if (st[0] == 'O' && st[st.size() - 1] == 'L') {
                    a.push_back(F[(st.size() - 1) / 2]);
                }
                if (st[0] == 'L' && st[st.size() - 1] == 'O') {
                    a.push_back(F[(st.size() - 1) / 2]);
                }
                if (st[0] == 'L' && st[st.size() - 1] == 'L') {
                    a.push_back(F[(st.size()) / 2]);
                }
            }
            st.clear();
        }
        st.push_back(s[i]);
    }
    int AllF = F[ans1];
    int S = 1;
    for (auto f : a) {
        S = (S * f) % mod;
    }
    int D = (modInverse(S, mod) * AllF) % mod;
    return (D * R(s)) % mod;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;
    string s; cin >> s;

    F.resize(200005);
    F[0] = 1;
    for (int i = 1; i < 200005; i++) {
        F[i] = (F[i - 1] * i) % mod;
    }

    P1.resize(200005); // O...O
    P1[3] = 1;
    P1[5] = 3;
    for (int i = 7; i < 200005; i += 2) {
        P1[i] = P1[i - 2] * (i - 2);
        P1[i] %= mod;
    }

    P2.resize(200005); // O...L
    P2[2] = 1;
    P2[4] = 2;
    for (int i = 6; i < 200005; i += 2) {
        P2[i] = P2[i - 2] * (i - 2);
        P2[i] %= mod;
    }

    P3.resize(200005); // L...O
    P3[2] = 1;
    P3[4] = 2;
    for (int i = 6; i < 200005; i += 2) {
        P3[i] = P3[i - 2] * (i - 2);
        P3[i] %= mod;
    }

    P4.resize(200005); // L...L
    P4[3] = 1;
    P4[5] = 3;
    for (int i = 7; i < 200005; i += 2) {
        P4[i] = P4[i - 2] * (i - 2);
        P4[i] %= mod;
    }

    ans1 = Ans1(s);
    ans2 = Ans2(s);

    cout << ans1 << ' ' << ans2;

    return 0;
}
