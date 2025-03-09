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

class SegmentTree {
public:
    struct Node {
        int ans;
        int open;
        int close;

        Node(int f, int s, int t) {
            ans = f;
            open = s;
            close = t;
        }

        Node() {
            ans = 0;
            open = 0;
            close = 0;
        }
    };

    SegmentTree(vector<int> a) {
        int n = a.size();

        N = 1;
        while (N < n) {
            N *= 2;
        }

        for (int i = 0; i < N - n; i++) {
            a.push_back(1);
        }

        Tree.resize(2 * N);

        for (int i = N; i < 2 * N; i++) {
            if (a[i - N] == 1) {
                Node newnode(0, 1, 0);
                Tree[i] = newnode;
            }
            else {
                Node newnode(0, 0, 1);
                Tree[i] = newnode;
            }
        }

        for (int i = N - 1; i > 0; i--) {
            Tree[i] = Merge(Tree[i * 2], Tree[i * 2 + 1]);
        }
    }

    int query(int l, int r) {
        return private_query(1, 0, N - 1, l, r).ans;
    }

private:
    int N;
    vector<Node> Tree;

    Node Merge(Node node1, Node node2) {
        int t = min(node1.open, node2.close);

        Node newnode(node1.ans + node2.ans + t * 2, 
            node1.open + node2.open - t, 
            node1.close + node2.close - t);

        return newnode;
    }

    Node private_query(int v, int l, int r, int cl, int cr) {
        if (r < cl || l > cr) {
            return Node();
        }

        if (l >= cl && r <= cr) {
            return Tree[v];
        }

        int m = (l + r) / 2;

        return Merge(
            private_query(v * 2, l, m, cl, cr),
            private_query(v * 2 + 1, m + 1, r, cl, cr)
        );
    }
};

void Solve() {
    string s; cin >> s;

    vector<int> a(s.size());
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            a[i] = 1;
        }
        else {
            a[i] = -1;
        }
    }

    SegmentTree ST(a);

    int Q; cin >> Q;
    for (int q = 0; q < Q; q++) {
        int l, r; cin >> l >> r;
        --l;
        --r;
        cout << ST.query(l, r) << '\n';
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
