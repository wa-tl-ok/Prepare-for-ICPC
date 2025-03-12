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

class Hash {
public:
    Hash(string S) {
        s = S; Get_random();

        Step1.resize(MX);
        Step2.resize(MX);

        Step1[0] = Step2[0] = 1;

        for (int i = 1; i < MX; i++) {
            Step1[i] = (Step1[i - 1] * base1) % mod1;
            Step2[i] = (Step2[i - 1] * base2) % mod2;
        }

        PHash1.resize(S.size());
        PHash2.resize(S.size());

        PHash1[0] = (S[0] - 'a' + 1) % mod1;
        PHash2[0] = (S[0] - 'a' + 1) % mod2;

        for (int i = 1; i < (int)S.size(); ++i) {
            PHash1[i] = (PHash1[i - 1] + ((S[i] - 'a' + 1) * Step1[i]) % mod1) % mod1;
            PHash2[i] = (PHash2[i - 1] + ((S[i] - 'a' + 1) * Step2[i]) % mod2) % mod2;
        }

        reverse(S.begin(), S.end());

        RHash1.resize(S.size());
        RHash2.resize(S.size());

        RHash1[0] = (S[0] - 'a' + 1) % mod1;
        RHash2[0] = (S[0] - 'a' + 1) % mod2;

        for (int i = 1; i < (int)S.size(); ++i) {
            RHash1[i] = (RHash1[i - 1] + ((S[i] - 'a' + 1) * Step1[i]) % mod1) % mod1;
            RHash2[i] = (RHash2[i - 1] + ((S[i] - 'a' + 1) * Step2[i]) % mod2) % mod2;
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

    pair<int, int> SP(vector<pair<int, int>> v) {
        pair<int, int> ans = { 0, 0 };
        int len = 0;

        for (auto p : v) {
            int l = p.first;
            int r = p.second;

            ans.first = (ans.first + Take_PHash1(l, r, len)) % mod1;
            ans.second = (ans.second + Take_PHash2(l, r, len)) % mod2;

            len += (r - l + 1);
        }

        return ans;
    }

    pair<int, int> SR(vector<pair<int, int>> v) {
        reverse(v.begin(), v.end());

        pair<int, int> ans = { 0, 0 };
        int len = 0;

        for (auto p : v) {
            int l = p.first;
            int r = p.second;

            ans.first = (ans.first + Take_RHash1(s.size() - r - 1, s.size() - l - 1, len)) % mod1;
            ans.second = (ans.second + Take_RHash2(s.size() - r - 1, s.size() - l - 1, len)) % mod2;

            len += (r - l + 1);
        }

        return ans;
    }

    bool Check(int l, int r) {
        return P(l, r) == R(l, r);
    }

private:
    string s;
    int MX = 2000005;

    int mod1, base1, mod2, base2;

    vector<int> Step1;
    vector<int> Step2;

    vector<int> PHash1;
    vector<int> PHash2;

    vector<int> RHash1;
    vector<int> RHash2;

    void Get_random() {
        std::random_device rd;
        std::mt19937 eng(rd());

        std::uniform_int_distribution<int> dist(0, 3);

        int m1 = dist(eng);
        int b1 = dist(eng);
        int m2 = dist(eng);
        int b2 = dist(eng);

        vector<int> mod = { 998244353, 1000000007, 1000000009, 1200720071 };
        vector<int> bases = { 61, 53, 31, 29 };

        mod1 = mod[0];
        mod2 = mod[1];
        base1 = bases[0];
        base2 = bases[1];
    }

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

    int Take_PHash1(int l, int r, int x) {
        if (l == 0) {
            return ((PHash1[r] + mod1) % mod1 * Step1[s.size() + x]) % mod1;
        }
        return ((PHash1[r] - PHash1[l - 1] + mod1) % mod1 * Step1[s.size() - l + x]) % mod1;
    }

    int Take_PHash2(int l, int r, int x) {
        if (l == 0) {
            return ((PHash2[r] + mod2) % mod2 * Step2[s.size() + x]) % mod2;
        }
        return ((PHash2[r] - PHash2[l - 1] + mod2) % mod2 * Step2[s.size() - l + x]) % mod2;
    }

    int Take_RHash1(int l, int r, int x) {
        if (l == 0) {
            return ((RHash1[r] + mod1) % mod1 * Step1[s.size() + x]) % mod1;
        }
        return ((RHash1[r] - RHash1[l - 1] + mod1) % mod1 * Step1[s.size() - l + x]) % mod1;
    }

    int Take_RHash2(int l, int r, int x) {
        if (l == 0) {
            return ((RHash2[r] + mod2) % mod2 * Step2[s.size() + x]) % mod2;
        }
        return ((RHash2[r] - RHash2[l - 1] + mod2) % mod2 * Step2[s.size() - l + x]) % mod2;
    }
};

void Solve() {
    string s; cin >> s;
    Hash hash(s);

    for (int z = s.size() / 2 + 1; z < s.size(); z++) {
        int l1 = 0;
        int r1 = z - 1;

        int l2 = (int)s.size() - z;
        int r2 = (int)s.size() - 1;

        if (hash.P(l1, r1) == hash.P(l2, r2)) {
            cout << "YES\n";
            for (int i = 0; i < z; i++) {
                cout << s[i];
            }
            return;
        }
    }

    cout << "NO\n";
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
