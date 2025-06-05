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

class Hash {
public:
    Hash(vector<int> S) {
        s = S;

        Step1.resize(MX);
        Step2.resize(MX);

        Step1[0] = Step2[0] = 1;

        for (int i = 1; i < MX; i++) {
            Step1[i] = (Step1[i - 1] * base1) % mod1;
            Step2[i] = (Step2[i - 1] * base2) % mod2;
        }

        PHash1.resize(S.size());
        PHash2.resize(S.size());

        PHash1[0] = (S[0] + 1) % mod1;
        PHash2[0] = (S[0] + 1) % mod2;

        for (int i = 1; i < (int)S.size(); ++i) {
            PHash1[i] = (PHash1[i - 1] + ((S[i] + 1) * Step1[i]) % mod1) % mod1;
            PHash2[i] = (PHash2[i - 1] + ((S[i] + 1) * Step2[i]) % mod2) % mod2;
        }

        reverse(S.begin(), S.end());

        RHash1.resize(S.size());
        RHash2.resize(S.size());

        RHash1[0] = (S[0] + 1) % mod1;
        RHash2[0] = (S[0] + 1) % mod2;

        for (int i = 1; i < (int)S.size(); ++i) {
            RHash1[i] = (RHash1[i - 1] + ((S[i] + 1) * Step1[i]) % mod1) % mod1;
            RHash2[i] = (RHash2[i - 1] + ((S[i] + 1) * Step2[i]) % mod2) % mod2;
        }

        reverse(S.begin(), S.end());
    }

    pair<int, int> P(int l, int r) {
        int a = Take_PHash1(l, r);
        int b = Take_PHash2(l, r);
        return { a, b };
    }

    pair<int, int> R(int l, int r) {
        int a = Take_RHash1(s.size() - r - 1, s.size() - l - 1);
        int b = Take_RHash2(s.size() - r - 1, s.size() - l - 1);
        return { a, b };
    }

private:
    vector<int> s;
    int MX = 300005;

    int mod1 = 1000000009, base1 = 998244353, mod2 = 1200720071, base2 = 1000000007;

    vector<int> Step1;
    vector<int> Step2;

    vector<int> PHash1;
    vector<int> PHash2;

    vector<int> RHash1;
    vector<int> RHash2;

    int Take_PHash1(int l, int r) {
        if (l == 0) {
            return ((PHash1[r] + mod1) % mod1 * Step1[s.size()]) % mod1;
        }
        return ((PHash1[r] - PHash1[l - 1] + mod1) % mod1 * Step1[s.size() - l]) % mod1;
    }

    int Take_PHash2(int l, int r) {
        if (l == 0) {
            return ((PHash2[r] + mod2) % mod2 * Step2[s.size()]) % mod2;
        }
        return ((PHash2[r] - PHash2[l - 1] + mod2) % mod2 * Step2[s.size() - l]) % mod2;
    }

    int Take_RHash1(int l, int r) {
        if (l == 0) {
            return ((RHash1[r] + mod1) % mod1 * Step1[s.size()]) % mod1;
        }
        return ((RHash1[r] - RHash1[l - 1] + mod1) % mod1 * Step1[s.size() - l]) % mod1;
    }

    int Take_RHash2(int l, int r) {
        if (l == 0) {
            return ((RHash2[r] + mod2) % mod2 * Step2[s.size()]) % mod2;
        }
        return ((RHash2[r] - RHash2[l - 1] + mod2) % mod2 * Step2[s.size() - l]) % mod2;
    }
};

void Solve() {
    int n, k; cin >> n >> k;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];

        if (i % 2 == 1) {
            a[i] ^= k;
        }
    }

    Hash H(a);

    int L = 0;
    int R;
    if (n % 2 == 0) {
        R = n;
    }
    else {
        R = n - 1;
    }
    L -= 2;
    R += 2;

    int ans = -1;

    while (L + 2 != R) {
        int M = (L + R) / 2;

        if (M % 2 == 1) {
            M -= 1;
        }

        int t = -1;

        for (int i = 0; i < n && i + M - 1 < n; i++) {
            int l1 = i;
            int r1 = i + M / 2 - 1;
            int l2 = i + M / 2;
            int r2 = i + M - 1;

            if (H.P(l1, r1) == H.R(l2, r2)) {
                t = l2;
                break;
            }
        }

        if (t == -1) {
            R = M;
        }
        else {
            ans = t;
            L = M;
        }
    }

    if (ans == -1) {
        cout << -1;
    }
    else {
        cout << ans + 1;
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
