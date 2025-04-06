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

struct Int {
    int value;
    static const int mod = 998244353;

    Int() : value(0) {}

    Int(int value) : value(normalize(value)) {}

    Int(const Int& other) : value(other.value) {}

    static int normalize(int x) {
        if (x < 0) {
            x += mod;
        }
        return x % mod;
    }

    Int operator+(const Int& other) const {
        return Int(value + other.value);
    }

    Int operator-(const Int& other) const {
        return Int(value - other.value);
    }

    Int operator*(const Int& other) const {
        return Int(static_cast<int>(1LL * value * other.value % mod));
    }

    Int operator/(const Int& other) const {
        return *this * other.inv();
    }

    Int pow(int exp) const {
        Int result(1);
        Int base(*this);
        while (exp > 0) {
            if (exp % 2 == 1) {
                result *= base;
            }
            base *= base;
            exp /= 2;
        }
        return result;
    }

    Int inv() const {
        return pow(mod - 2);
    }

    Int& operator=(int newValue) {
        value = normalize(newValue);
        return *this;
    }

    Int& operator+=(const Int& other) {
        value = normalize(value + other.value);
        return *this;
    }

    Int& operator-=(const Int& other) {
        value = normalize(value - other.value);
        return *this;
    }

    Int& operator*=(const Int& other) {
        value = normalize(static_cast<int>(1LL * value * other.value % mod));
        return *this;
    }

    Int& operator/=(const Int& other) {
        return *this *= other.inv();
    }

    friend std::ostream& operator<<(std::ostream& os, const Int& obj) {
        os << obj.value;
        return os;
    }
};

vector<Int> factorials;

Int Find_C_n_k(int n, int k) {
    Int f = factorials[n];
    Int s = factorials[k];
    Int t = factorials[n - k];

    return (f / (s * t));
}

void Solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int F = 0; int D = 0; int S = 0;
    for (int i = 0; i < n; i += 3) {
        if (a[i] == a[i + 1] && a[i + 1] == a[i + 2]) {
            F++;
        }
        else if (a[i] == a[i + 1] && a[i + 1] < a[i + 2] || 
                 a[i + 1] == a[i + 2] && a[i + 2] < a[i] || 
                 a[i + 2] == a[i] && a[i] < a[i + 1]) {
            D++;
        }
    } S = n / 3 - F;

    Int ans = 0;

    for (int brr = 0; brr <= F; brr++) {
        int rbb = F - brr;

        int blue = rbb * 2 + brr;
        int red = brr * 2 + rbb;

        int needbrr = 0;
        int needrbb = 0;

        if (blue > red) {
            needbrr = blue - red;
        }
        else {
            needrbb = red - blue;
        }

        int Sum = needbrr + needrbb;

        needbrr += (S - Sum) / 2;
        needrbb += (S - Sum) / 2;

        if (needbrr < 0 || needbrr > S || needrbb < 0 || needrbb > S || Sum < 0 || Sum > S) {
            continue;
        }

        ans += Int(3).pow(F) * Int(2).pow(D) * Find_C_n_k(F, brr) *  Find_C_n_k(S, needbrr);
    }

    cout << ans << '\n';
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    factorials.push_back(Int(1));
    for (int i = 1; i <= 1'000'000; i++) {
        factorials.push_back(Int(factorials.back() * i));
    }

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
