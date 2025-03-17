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
        tree1.resize(n + 1, 0);
        tree2.resize(n + 1, 0);
    }

    void plus(int l, int r, int x) {
        ++l;
        ++r;

        add(tree1, l, x);
        add(tree1, r + 1, -x);

        add(tree2, l, x * (l - 1));
        add(tree2, r + 1, -x * r);
    }

    int query(int l, int r) const {
        ++l;
        ++r;

        return range_query(r) - range_query(l - 1);
    }

private:
    vector<int> tree1, tree2;
    int size;

    void add(vector<int>& tree, int ind, int x) {
        while (ind <= size) {
            tree[ind] += x;
            ind += ind & -ind;
        }
    }

    int prefix_query(const vector<int>& tree, int ind) const {
        int sum = 0;
        while (ind > 0) {
            sum += tree[ind];
            ind -= ind & -ind;
        }
        return sum;
    }

    int range_query(int ind) const {
        return prefix_query(tree1, ind) * ind - prefix_query(tree2, ind);
    }
};

void Solve() {
    int n, m; cin >> n >> m;
    vector<int> r(n);
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }

    vector<int> ps(n);
    if (r[0] == 0) {
        ps[0] = 1;
    }
    else {
        ps[0] = 0;
    }
    for (int i = 1; i < n; i++) {
        ps[i] = ps[i - 1];
        if (r[i] == 0) {
            ++ps[i];
        }
    }

    vector<int> I(m + 1, 0);
    FenwickTree Add_Lazy(m + 1);
    
    for (int q = 0; q < n; q++) {
        if (r[q] == 0) {
            vector<int> new_I(m + 1);
            for (int i = 0; i <= m; i++) {
                int Current_Add_lazy = Add_Lazy.query(i, i);
                new_I[i] = max(new_I[i], I[i] + Current_Add_lazy);
                if (i + 1 <= m) {
                    new_I[i + 1] = max(new_I[i + 1], I[i] + Current_Add_lazy);
                }
                Add_Lazy.plus(i, i, -Current_Add_lazy);
            }
            I = new_I; 
        }
        else if (r[q] > 0 && abs(r[q]) <= m && abs(r[q]) <= ps[q]) {
            Add_Lazy.plus(abs(r[q]), ps[q], 1);
        }
        else if (r[q] < 0 && abs(r[q]) <= m && abs(r[q]) <= ps[q]) {
            Add_Lazy.plus(0, ps[q] - abs(r[q]), 1);
        }
    }

    vector<int> new_I(m + 1);
    for (int i = 0; i <= m; i++) {
        int Current_Add_lazy = Add_Lazy.query(i, i);
        new_I[i] = max(new_I[i], I[i] + Current_Add_lazy);
        if (i + 1 <= m) {
            new_I[i + 1] = max(new_I[i + 1], I[i] + Current_Add_lazy);
        }
        Add_Lazy.plus(i, i, -Current_Add_lazy);
    }
    I = new_I;

    int ans = 0;
    for (int i = 0; i <= m; i++) {
        ans = max(ans, I[i]);
    }
    cout << ans;
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
