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

int BLOCK_SIZE = 1000;

class Mo {
public:
    struct QUERY {
        int l;
        int r;
        int id;

        bool operator<(const QUERY& other) const {
            int block1 = l / BLOCK_SIZE;
            int block2 = other.l / BLOCK_SIZE;

            if (block1 != block2) {
                return block1 < block2;
            }

            if (block1 % 2 == 1) {
                return r < other.r;
            }
            else {
                return r > other.r;
            }
        }
    };





    // --- STATE --- //

    unordered_map<int, int> cnt;

    void ADD(int G) {
        cnt[a[G]] += 1;
    }

    void REM(int G) {
        cnt[a[G]] -= 1;
    }

    void add_right() {
        R++;
        ADD(R);
    }

    void add_left() {
        L--;
        ADD(L);
    }

    void rem_right() {
        REM(R);
        R--;
    }

    void rem_left() {
        REM(L);
        L++;
    }

    auto get_ans() {
        if (query_min(L, R) == query_gcd(L, R)) {
            return R - L + 1 - cnt[query_min(L, R)];
        }
        else {
            return R - L + 1;
        }
    }

    // --- STATE --- //





    Mo(vector<pair<int, int>> Q_, vector<int> a_) : a(a_) {
        BUILD(a);

        BLOCK_SIZE = (int)sqrt((int)a.size()) + 1;

        for (int i = 0; i < (int)Q_.size(); i++) {
            Q.push_back({ Q_[i].first, Q_[i].second, i });
        }
        sort(Q.begin(), Q.end());

        ans.resize((int)Q.size());
        L = 0; R = -1;
    }

    void GO() {
        for (int i = 0; i < (int)ans.size(); i++) {
            while (R < Q[i].r) {
                add_right();
            }

            while (L > Q[i].l) {
                add_left();
            }

            while (R > Q[i].r) {
                rem_right();
            }

            while (L < Q[i].l) {
                rem_left();
            }

            ans[Q[i].id] = get_ans();
        }
    }

    void print_ans() {
        for (auto p : ans) {
            cout << p << ' ';
        }
    }

private:
    vector<int> ans;

    vector<QUERY> Q;
    vector<int> a;

    int L, R;



    int gcd(int a, int b) {
        while (b != 0) {
            int temp = b; b = a % b; a = temp;
        }
        return a;
    }

    int N, K;
    int neutral = 1;

    vector<vector<int>> Stable_min;
    vector<vector<int>> Stable_gcd;
    vector<int> highestBit;
    vector<int> aaa;

    int Function_min(int left, int right) {
        return min(left, right);
    }

    int Function_gcd(int left, int right) {
        return gcd(left, right);
    }

    void BUILD(const vector<int>& vec) {
        for (auto p : vec) {
            aaa.push_back(p);
        }

        this->K = 0;

        int n = (int)vec.size();
        int p = 1;
        while (p < n) {
            p <<= 1;
            ++(this->K);
        }

        for (int i = 0; i < p - n; i++) {
            aaa.push_back(neutral);
        }

        this->N = (int)aaa.size();

        highestBit.resize(N);
        highestBit[0] = 0;
        highestBit[1] = 0;
        for (int i = 2; i < N; i++) {
            highestBit[i] = highestBit[i >> 1] + 1;
        }

        Stable_min.resize(N);
        for (int i = 0; i < N; i++) {
            Stable_min[i].resize(K);
            Stable_min[i][0] = aaa[i];
        }

        int sz = 1;
        for (int lvl = 1; lvl < K; lvl++) {
            sz = sz <<= 1;
            for (int c = sz; c < N; c += sz << 1) {
                Stable_min[c][lvl] = aaa[c];
                for (int i = c + 1; i < c + sz; i++) {
                    Stable_min[i][lvl] = Function_min(Stable_min[i - 1][lvl], aaa[i]);
                }

                Stable_min[c - 1][lvl] = aaa[c - 1];
                for (int i = c - 2; i >= c - sz; i--) {
                    Stable_min[i][lvl] = Function_min(aaa[i], Stable_min[i + 1][lvl]);
                }
            }
        }

        Stable_gcd.resize(N);
        for (int i = 0; i < N; i++) {
            Stable_gcd[i].resize(K);
            Stable_gcd[i][0] = aaa[i];
        }

        sz = 1;
        for (int lvl = 1; lvl < K; lvl++) {
            sz = sz <<= 1;
            for (int c = sz; c < N; c += sz << 1) {
                Stable_gcd[c][lvl] = aaa[c];
                for (int i = c + 1; i < c + sz; i++) {
                    Stable_gcd[i][lvl] = Function_gcd(Stable_gcd[i - 1][lvl], aaa[i]);
                }

                Stable_gcd[c - 1][lvl] = aaa[c - 1];
                for (int i = c - 2; i >= c - sz; i--) {
                    Stable_gcd[i][lvl] = Function_gcd(aaa[i], Stable_gcd[i + 1][lvl]);
                }
            }
        }
    }

    int query_min(int left, int right) {
        if (left == right) {
            return aaa[left];
        }
        else {
            int lvl = highestBit[left ^ right];
            return Function_min(Stable_min[left][lvl], Stable_min[right][lvl]);
        }
    }

    int query_gcd(int left, int right) {
        if (left == right) {
            return aaa[left];
        }
        else {
            int lvl = highestBit[left ^ right];
            return Function_gcd(Stable_gcd[left][lvl], Stable_gcd[right][lvl]);
        }
    }
};

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<pair<int, int>> Q;
    int q; cin >> q;

    for (int i = 0; i < q; i++) {
        int l, r; cin >> l >> r;
        --l;
        --r;
        Q.push_back({ l, r, });
    }

    Mo W(Q, a);
    W.GO();
    W.print_ans();
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
