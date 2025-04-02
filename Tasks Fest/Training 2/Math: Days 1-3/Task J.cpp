#define _CRT_SECURE_NO_WARNINGS 

#include <iostream> 
#include <algorithm> 
#include <cmath> 
#include <climits> 
#include <vector> 
#include <queue> 
#include <deque> 
#include <array> 
#include <list> 
#include <stack> 
#include <tuple> 
#include <set> 
#include <unordered_set> 
#include <map> 
#include <unordered_map> 
#include <string> 
#include <cstring> 
#include <random> 
#include <bitset> 
#include <iomanip> 
#include <iterator> 
#include <functional> 
#include <ctime> 
#include <chrono> 
#include <cctype> 
#include <fstream> 
#include <ranges> 
#include <numeric> 
#include <complex> 
#include <cassert> 

using namespace std;

// #pragma GCC optimize("Ofast") 
// #pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

#define int               long long 
#define sz(x)             ((int)(x).size()) 
#define mp                make_pair 
#define all(x)            (x).begin(), (x).end() 
#define pb                push_back 
#define pf                push_front 
#define ff                first 
#define ss                second 
#define unique(x)         (x).erase(unique(all(x)), (x).end()) 
#define min3(a, b, c)     min(a, min(b, c)) 
#define max3(a, b, c)     max(a, max(b, c)) 
#define FOR(i, a, b)      for (int i = (a); i <= (b); i++) 
#define ROF(i, a, b)      for (int i = (a); i >= (b); i--) 

using vi = vector<int>;
using vd = vector<double>;
using vpii = vector<pair<int, int>>;
using vpdd = vector<pair<double, double>>;
using pii = pair<int, int>;
using pdd = pair<double, double>;

template <typename Container>
void PRINT(const Container& container) {
    for (const auto& e : container) {
        cout << e << ' ';
    } cout << '\n';
}

void print_double(double ans, int num) {
    cout << fixed << setprecision(num) << ans << '\n';
}

const int inf = 1e18;
const double eps = 1e-9;
const double PI = 3.141592653589793;

string alh = "abcdefghijklmnopqrstuvwxyz";
string ALH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

int get(vector<int>& ps, int l, int r) {
    if (l == 0) {
        return ps[r];
    }
    return ps[r] - ps[l - 1];
}

pair<int, int> F(vector<int>& a, vector<int>& ps, int cl, int cr) {
    int S = get(ps, cl, cr);

    int l1 = cl;
    int r1 = cr;

    while (l1 + 1 != r1) {
        int m = (l1 + r1) / 2;

        if (get(ps, cl, m) < S / 2) {
            l1 = m;
        }
        else {
            r1 = m;
        }
    }

    int l2 = cl;
    int r2 = cr;

    while (l2 + 1 != r2) {
        int m = (l2 + r2) / 2;

        if (get(ps, cl, m) > S / 2) {
            r2 = m;
        }
        else {
            l2 = m;
        }
    }

    return { l1, r2 };
}

int BS1(vector<int>& a, int cl, int cr) {
    if (a[a.size() - 1] < cl) {
        return inf;
    }

    int l = -1;
    int r = a.size();

    while (l + 1 != r) {
        int m = (l + r) / 2;

        if (a[m] < cl) {
            l = m;
        }
        else {
            r = m;
        }
    }

    return a[r];
}

int BS2(vector<int>& a, int cl, int cr) {
    if (a[0] > cr) {
        return -inf;
    }

    int l = -1;
    int r = a.size();

    while (l + 1 != r) {
        int m = (l + r) / 2;

        if (a[m] > cr) {
            r = m;
        }
        else {
            l = m;
        }
    }

    return a[l];
}

int get_L(map<int, vector<int>>& pos, vector<int>& px, int l, int r) {
    return BS1(pos[px[r]], l, r);
}

int get_R(map<int, vector<int>>& pos, vector<int>& px, int l, int r) {
    int v = -1;

    if (l == 0) {
        v = 0;
    }
    else {
        v = px[l - 1];
    }

    int R = -1;

    if (pos[0].size() > 0) {
        R = BS2(pos[v], l, r);
    }
    else {
        R = -inf;
    }

    return R;
}

void Solve() {
    int n, q; cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<vector<int>> A(32);
    for (int i = 0; i < 32; i++) {
        A[i].resize(n);
    }

    for (int i = 0; i < 32; i++) {
        for (int j = 0; j < n; j++) {
            if (a[j] & (1 << i)) {
                A[i][j] = 1;
            }
        }
    }

    vector<vector<int>> PS(32);
    for (int i = 0; i < 32; i++) {
        PS[i].resize(n);
    }

    for (int i = 0; i < 32; i++) {
        int s = 0;
        for (int j = 0; j < n; j++) {
            s += A[i][j];
            PS[i][j] = s;
        }
    }

    vector<int> px(n);
    int x = 0;
    for (int i = 0; i < n; i++) {
        x = x ^ a[i];
        px[i] = x;
    }

    map<int, vector<int>> pos;
    for (int i = 0; i < n; i++) {
        pos[px[i]].push_back(i);
    }

    for (int qq = 0; qq < q; qq++) {
        int l, r; cin >> l >> r;

        --l;
        --r;

        vector<pair<int, int>> G;
        bool Flag = true;

        for (int i = 0; i < 32; i++) {
            int S = get(PS[i], l, r);

            if (S % 2 == 1) {
                if (S == 1) {
                    G.push_back({ inf, -inf });
                }
                else {
                    Flag = false;
                    break;
                }
            }
            else {
                if (S == 0) {
                    G.push_back({ -inf, inf });
                }
                else {
                    G.push_back(F(A[i], PS[i], l, r));
                }
            }
        }

        int mxl = -inf;
        int mnr = inf;

        for (auto [L, R] : G) {
            mxl = max(mxl, L);
            mnr = min(mnr, R);
        }

        if (Flag == true) {
            if (mxl < mnr) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
        else {
            if (get_L(pos, px, l, r) <= get_R(pos, px, l, r)) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }

    cout << endl;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    /*
                      ________________
                     / Just solved it \
                     |   in my mind   |
                     \________________/
                    /
                   /
　　　　　／＞　 フ         ___________
　　　　　| 　_　 _|       |          |
　 　　　／`ミ _x 彡       |   WA 2   |
　　 　 /　　　 　 |       |__________|
　　　 /　 ヽ　　 ﾉ        /          /
　／￣|　　 |　|　|       /_________ /
　| (￣ヽ＿_ヽ_)_)
　＼二つ

    */

    /*
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    */

    // auto start = chrono::high_resolution_clock::now();

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

    // auto end = chrono::high_resolution_clock::now();

    /*
    cout << "Time taken: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " milliseconds" << endl;
    */

    return 0;
}
