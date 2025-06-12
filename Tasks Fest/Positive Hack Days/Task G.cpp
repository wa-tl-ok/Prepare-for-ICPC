// #define _CRT_SECURE_NO_WARNINGS 

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

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

template<typename T> using min_heap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> using max_heap = priority_queue<T>;

#define BIT(n) (1LL << (n))
#define HAS_BIT(x, n) (((x) >> (n)) & 1)
#define SET_BIT(x, n) ((x) | BIT(n))

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

vector<vector<int>> wr, rd;
vector<bool> buf(1000005);

bool blocks(int i, int j) {
    for (auto u : wr[i]) {
        buf[u] = true;
    }

    for (auto u : rd[j]) {
        if (buf[u] == true) {
            for (auto k : wr[i]) {
                buf[k] = false;
            }

            return true;
        }
    }

    for (auto k : wr[i]) {
        buf[k] = false;
    }

    return false;
}

bool cmp0(int i, int j) {
    bool b1 = true;
    bool b2 = true;

    int wi = wr[i].size();
    int ri = rd[i].size();
    int wj = wr[j].size();
    int rj = rd[j].size();

    int score1 = wi;
    int score2 = wj;

    b1 = blocks(i, j);
    b2 = blocks(j, i);

    if (b1 == false && b2 == false) {
        if (score1 != score2) {
            return score1 < score2;
        }

        if (wi != wj) {
            return wi < wj;
        }

        return ri < rj;
    }

    if (b1 == false) {
        return true;
    }

    if (b2 == false) {
        return false;
    }

    if (score1 != score2) {
        return score1 < score2;
    }

    if (wi != wj) {
        return wi < wj;
    }

    return ri < rj;
}

bool cmp1(int i, int j) {
    bool b1 = true;
    bool b2 = true;

    int wi = wr[i].size();
    int ri = rd[i].size();
    int wj = wr[j].size();
    int rj = rd[j].size();

    int score1 = wi * rj;
    int score2 = wj * ri;

    b1 = blocks(i, j);
    b2 = blocks(j, i);

    if (b1 == false && b2 == false) {
        if (score1 != score2) {
            return score1 < score2;
        }

        if (wi != wj) {
            return wi < wj;
        }

        return ri < rj;
    }

    if (b1 == false) {
        return true;
    }

    if (b2 == false) {
        return false;
    }

    if (score1 != score2) {
        return score1 < score2;
    }

    if (wi != wj) {
        return wi < wj;
    }

    return ri < rj;
}

bool cmp2(int i, int j) {
    bool b1 = true;
    bool b2 = true;

    int wi = wr[i].size();
    int ri = rd[i].size();
    int wj = wr[j].size();
    int rj = rd[j].size();

    int score1 = wi + rj;
    int score2 = wj + ri;

    b1 = blocks(i, j);
    b2 = blocks(j, i);

    if (b1 == false && b2 == false) {
        if (score1 != score2) {
            return score1 < score2;
        }

        if (wi != wj) {
            return wi < wj;
        }

        return ri < rj;
    }

    if (b1 == false) {
        return true;
    }

    if (b2 == false) {
        return false;
    }

    if (score1 != score2) {
        return score1 < score2;
    }

    if (wi != wj) {
        return wi < wj;
    }

    return ri < rj;
}

bool cmp3(int i, int j) {
    bool b1 = true;
    bool b2 = true;

    int wi = wr[i].size();
    int ri = rd[i].size();
    int wj = wr[j].size();
    int rj = rd[j].size();

    int score1 = wi * (rj + 1);
    int score2 = wj * (ri + 1);

    b1 = blocks(i, j);
    b2 = blocks(j, i);

    if (b1 == false && b2 == false) {
        if (score1 != score2) {
            return score1 < score2;
        }

        if (wi != wj) {
            return wi < wj;
        }

        return ri < rj;
    }

    if (b1 == false) {
        return true;
    }

    if (b2 == false) {
        return false;
    }

    if (score1 != score2) {
        return score1 < score2;
    }

    if (wi != wj) {
        return wi < wj;
    }

    return ri < rj;
}

bool cmp0_(int i, int j) {
    bool b1 = true;
    bool b2 = true;

    int wi = wr[i].size();
    int ri = rd[i].size();
    int wj = wr[j].size();
    int rj = rd[j].size();

    int score1 = wi;
    int score2 = wj;

    b1 = blocks(i, j);
    b2 = blocks(j, i);

    if (b1 == false && b2 == false) {
        return score1 < score2;
    }

    if (b1 == false) {
        return true;
    }

    if (b2 == false) {
        return false;
    }

    if (wi == wj) {
        return ri < rj;
    }

    return wi < wj;
}

bool cmp1_(int i, int j) {
    bool b1 = true;
    bool b2 = true;

    int wi = wr[i].size();
    int ri = rd[i].size();
    int wj = wr[j].size();
    int rj = rd[j].size();

    int score1 = wi * rj;
    int score2 = wj * ri;

    b1 = blocks(i, j);
    b2 = blocks(j, i);

    if (b1 == false && b2 == false) {
        return score1 < score2;
    }

    if (b1 == false) {
        return true;
    }

    if (b2 == false) {
        return false;
    }

    if (score1 == score2) {
        return wi < wj;
    }

    return score1 < score2;
}

bool cmp2_(int i, int j) {
    bool b1 = true;
    bool b2 = true;

    int wi = wr[i].size();
    int ri = rd[i].size();
    int wj = wr[j].size();
    int rj = rd[j].size();

    int score1 = wi + rj;
    int score2 = wj + ri;

    b1 = blocks(i, j);
    b2 = blocks(j, i);

    if (b1 == false && b2 == false) {
        return score1 < score2;
    }

    if (b1 == false) {
        return true;
    }

    if (b2 == false) {
        return false;
    }

    if (score1 == score2) {
        return wi < wj;
    }

    return score1 < score2;
}

void relax_answ(vector<int>& answ, vector<int>& ind) {
    vector<int> ans;
    set<int> used;

    for (auto u : ind) {
        bool can = true;

        for (auto k : rd[u]) {
            if (used.find(k) != used.end()) {
                can = 0;
                break;
            }
        }

        if (can == true) {
            for (auto k : wr[u]) {
                used.insert(k);
            }

            ans.push_back(u);
        }
    }

    if (ans.size() > answ.size()) {
        swap(ans, answ);
    }
}

void go(vector<int>& answ, vector<int>& ind) {
    sort(ind.begin(), ind.end(), cmp0_);
    relax_answ(answ, ind);

    sort(ind.begin(), ind.end(), cmp1_);
    relax_answ(answ, ind);

    sort(ind.begin(), ind.end(), cmp2_);
    relax_answ(answ, ind);
}

void Solve() {
    int n, m; cin >> n >> m;

    vector<int> answ;
    vector<int> ind;

    wr.resize(n);
    rd.resize(n);

    int len = 0;
    for (int i = 0; i < n; i++) {
        ind.push_back(i);

        int r, w; cin >> r >> w;
        rd[i].resize(r);
        wr[i].resize(w);

        for (int j = 0; j < r; j++) {
            cin >> rd[i][j];
            len++;
        }

        for (int j = 0; j < w; j++) {
            cin >> wr[i][j];
            len++;
        }
    }

    go(answ, ind);

    sort(ind.begin(), ind.end(), cmp0);
    relax_answ(answ, ind);

    sort(ind.begin(), ind.end(), cmp1);
    relax_answ(answ, ind);

    sort(ind.begin(), ind.end(), cmp2);
    relax_answ(answ, ind);

    sort(ind.begin(), ind.end(), cmp3);
    relax_answ(answ, ind);

    go(answ, ind);

    cout << answ.size() << '\n';
    for (auto u : answ) {
        cout << u + 1 << ' ';
    }
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
    freopen("task.in", "r", stdin);
    freopen("task.out", "w", stdout);
    */

    // auto start = chrono::high_resolution_clock::now();

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

    // auto end = chrono::high_resolution_clock::now();

    /*
    cout << "Time taken: "
         << chrono::duration_cast<chrono::milliseconds>(end - start).count()
         << " milliseconds" << endl;
    */

    return 0;
}
