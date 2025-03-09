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

class ImplicitSegmentTree {
public:
    ImplicitSegmentTree(int size) : n(size), root(nullptr) {}

    void change(int left, int right, int val) {
        root = updateRange(root, 0, n - 1, left, right, val);
    }

    int query(int left, int right) {
        return queryRange(root, 0, n - 1, left, right);
    }

private:
    struct Node {
        int minVal;
        int lazy;
        Node* left;
        Node* right;

        Node() : minVal(std::numeric_limits<int>::max()), lazy(0), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    void propagate(Node* node, int l, int r) {
        if (!node || node->lazy == 0) {
            return;
        }

        node->minVal = node->lazy;

        if (l != r) {
            if (!node->left) {
                node->left = new Node();
            }

            if (!node->right) {
                node->right = new Node();
            }

            node->left->lazy = node->lazy;
            node->right->lazy = node->lazy;
        }

        node->lazy = 0;
    }

    Node* updateRange(Node* node, int l, int r, int left, int right, int val) {
        if (!node) {
            node = new Node();
        }

        propagate(node, l, r);

        if (left > r || right < l) {
            return node;
        }

        if (left <= l && r <= right) {
            node->lazy = val;
            propagate(node, l, r);
            return node;
        }

        int mid = l + (r - l) / 2;

        node->left = updateRange(node->left, l, mid, left, right, val);
        node->right = updateRange(node->right, mid + 1, r, left, right, val);

        node->minVal = min(getMin(node->left), getMin(node->right));

        return node;
    }

    int queryRange(Node* node, int l, int r, int left, int right) {
        if (!node) {
            return std::numeric_limits<int>::max();
        }

        propagate(node, l, r);

        if (left > r || right < l) {
            return std::numeric_limits<int>::max();
        }

        if (left <= l && r <= right) {
            return node->minVal;
        }

        int mid = l + (r - l) / 2;

        return min(queryRange(node->left, l, mid, left, right),
            queryRange(node->right, mid + 1, r, left, right));
    }

    int getMin(Node* node) {
        return node ? node->minVal : std::numeric_limits<int>::max();
    }
};

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
    vector<pair<int, int>> Q;
    for (int i = 0; i < m; i++) {
        int l, r; cin >> l >> r;
        Q.push_back({ l, r });
    }

    sort(Q.begin(), Q.end());
    reverse(Q.begin(), Q.end());

    ImplicitSegmentTree BACK(n + 1);
    for (int i = 0; i <= n; i++) {
        BACK.change(i, i, i);
    }
    for (auto p : Q) {
        int l = p.ff;
        int r = p.ss;
        BACK.change(l, r, l);
    }

    FenwickTree CNT(n + 1);
    for (auto p : Q) {
        int l = p.ff;
        int r = p.ss;
        CNT.plus(l, r, 1);
    }

    vector<int> DP(n + 1);
    DP[0] = 0;
    for (int i = 1; i <= n; i++) {
        DP[i] = max(DP[i - 1], DP[BACK.query(i, i) - 1] + CNT.query(i, i));
    }

    cout << DP[n] << '\n';
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
