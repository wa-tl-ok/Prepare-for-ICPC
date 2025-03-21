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

class FenwickTree {
public:
    FenwickTree(int n) : size(n) {
        tree.resize(n + 1, 0);
    }

    void plus(int ind, long long x) {
        ++ind;
        while (ind <= size) {
            tree[ind] += x;
            ind += ind & -ind;
        }
    }

    void change(int ind, long long x) {
        ++ind;
        x = x - tree[ind];
        while (ind <= size) {
            tree[ind] += x;
            ind += ind & -ind;
        }
    }

    long long query(int ind) const {
        long long sum = 0;

        while (ind > 0) {
            sum += tree[ind];
            ind -= ind & -ind;
        }

        return sum;
    }

    long long range_query(int l, int r) const {
        ++l;
        ++r;
        return query(r) - query(l - 1);
    }
private:
    vector<long long> tree;
    int size;
};

void Solve() {
    int n, c; cin >> n >> c;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }

    FenwickTree FT(2 * c + 5);
    for (int i = 0; i < n; i++) {
        FT.plus(v[i], 1);
    }

    set<int> Array;
    for (auto p : v) {
        Array.insert(p);
    }

    vector<int> A;
    for (int a = 1; a <= c; a++) {
        if (Array.find(a) == Array.end()) {
            A.push_back(a);
        }
    }

    vector<int> Y;
    for (int y = 1; y <= c; y++) {
        if (Array.find(y) != Array.end()) {
            Y.push_back(y);
        }
    }

    for (int i = 0; i < A.size(); i++) {
        for (int j = 0; A[i] * Y[j] <= c && j < Y.size(); j++) {
            int a = A[i];
            int y = Y[j];

            int l = a * y;
            int r = (a + 1) * y - 1;

            if (FT.range_query(l, r) > 0) {
                cout << "No\n";
                return;
            }

            if (y * a > c) {
                break;
            }
        }
    }

    cout << "Yes\n";
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
