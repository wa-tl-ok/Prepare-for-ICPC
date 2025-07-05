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

    void plus(int pos, int val) {
        root = updatePoint(root, 0, n - 1, pos, val);
    }

    int query(int left, int right) {
        return queryRange(root, 0, n - 1, left, right);
    }

private:
    struct Node {
        int maxVal;
        Node* left;
        Node* right;

        Node() : maxVal(std::numeric_limits<int>::min()), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    Node* updatePoint(Node* node, int l, int r, int pos, int val) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            if (node->maxVal == std::numeric_limits<int>::min()) {
                node->maxVal = val;
            }
            else {
                node->maxVal += val;
            }

            return node;
        }

        int mid = l + (r - l) / 2;

        if (pos <= mid) {
            node->left = updatePoint(node->left, l, mid, pos, val);
        }
        else {
            node->right = updatePoint(node->right, mid + 1, r, pos, val);
        }

        node->maxVal = max(getMax(node->left), getMax(node->right));

        return node;
    }

    int queryRange(Node* node, int l, int r, int const_l, int const_r) {
        if (!node) {
            return std::numeric_limits<int>::min();
        }

        if (const_l > r || const_r < l) {
            return std::numeric_limits<int>::min();
        }

        if (const_l <= l && r <= const_r) {
            return node->maxVal;
        }

        int mid = l + (r - l) / 2;

        return max(queryRange(node->left, l, mid, const_l, const_r),
            queryRange(node->right, mid + 1, r, const_l, const_r));
    }

    int getMax(Node* node) {
        return node ? node->maxVal : std::numeric_limits<int>::min();
    }
};

int bs_rl(vector<int>& arr, int target) {
    /*
        Find min index of number that >= target
    */
    if (arr[arr.size() - 1] < target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

void Solve() {
    int n, m; cin >> n >> m;

    vector<int> powers(n);
    for (int i = 0; i < n; i++) {
        cin >> powers[i];
    }

    vector<int> tasks(m);
    for (int i = 0; i < m; i++) {
        cin >> tasks[i];

        if (tasks[i] <= powers[0]) {
            tasks[i] = inf;
        }
    }

    sort(tasks.begin(), tasks.end());
    reverse(tasks.begin(), tasks.end());

    vector<int> stronger;
    for (int i = 0; i < n; i++) {
        if (powers[i] > powers[0]) {
            stronger.push_back(powers[i]);
        }
    }

    if (stronger.size() == 0) {
        for (int k = 1; k <= m; k++) {
            cout << m / k << ' ';
        } cout << '\n';
        return;
    }

    sort(stronger.begin(), stronger.end());

    for (int i = 0; i < m; i++) {
        if (bs_rl(stronger, tasks[i]) == -1) {
            tasks[i] = 0;
        }
        else {
            tasks[i] = stronger.size() - bs_rl(stronger, tasks[i]);
        }
    }

    ImplicitSegmentTree ST(m);
    for (int i = 0; i < m; i++) {
        ST.plus(i, tasks[i]);
    }

    for (int k = 1; k <= m; k++) {
        int ans = 0;

        for (int i = 0; i < m; i += k) {
            int l = i;
            int r = i + k - 1;

            if (r < m) {
                ans += 1 + ST.query(l, r);
            }
            else {
                break;
            }
        }

        cout << ans << ' ';
    } 
    
    cout << '\n';
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
