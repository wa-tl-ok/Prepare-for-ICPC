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

#pragma GCC optimize("Ofast") 
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")

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

    void change(int pos, int val) {
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

        Node() : maxVal(0), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int n;

    Node* updatePoint(Node* node, int l, int r, int pos, int val) {
        if (!node) {
            node = new Node();
        }

        if (l == r) {
            node->maxVal = val;
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
            return 0;
        }

        if (const_l > r || const_r < l) {
            return 0;
        }

        if (const_l <= l && r <= const_r) {
            return node->maxVal;
        }

        int mid = l + (r - l) / 2;

        return max(queryRange(node->left, l, mid, const_l, const_r),
            queryRange(node->right, mid + 1, r, const_l, const_r));
    }

    int getMax(Node* node) {
        return node ? node->maxVal : 0;
    }
};

void G(const vector<pair<int, int>>& items, vector<pair<int, int>>& combinations) {
    int n = items.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        int c = 0;
        int w = 0;
        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                c += items[i].first;
                w += items[i].second;
            }
        }
        combinations.push_back({ w, c });
    }
}

void Solve() {
    int n, MX; cin >> n >> MX;

    vector<pair<int, int>> items(n);
    for (int i = 0; i < n; ++i) {
        cin >> items[i].first >> items[i].second;
    }

    vector<pair<int, int>> FH;
    for (int i = 0; i < n / 2; i++) {
        FH.push_back(items[i]);
    }
    vector<pair<int, int>> SH;
    for (int i = n / 2; i < n; i++) {
        SH.push_back(items[i]);
    }

    vector<pair<int, int>> F;
    vector<pair<int, int>> S;

    G(FH, F);
    G(SH, S);

    sort(F.begin(), F.end());
    sort(S.begin(), S.end());

    vector<pair<int, int>> UF;
    int mxf = 0;
    for (const auto c : F) {
        if (c.first <= MX) {
            if (c.second >= mxf) {
                mxf = c.second;
                UF.push_back(c);
            }
        }
        if (UF.size() > 1) {
            auto last = UF[UF.size() - 1];
            auto predlast = UF[UF.size() - 2];
            if (last.first == predlast.first) {
                if (last.second > predlast.second) {
                    swap(UF[UF.size() - 1], UF[UF.size() - 2]);
                    UF.pop_back();
                }
            }
        }
    }

    vector<pair<int, int>> US;
    int mxs = 0;
    for (const auto c : S) {
        if (c.first <= MX) {
            if (c.second >= mxs) {
                mxs = c.second;
                US.push_back(c);
            }
        }
        if (US.size() > 1) {
            auto last = US[US.size() - 1];
            auto predlast = US[US.size() - 2];
            if (last.first == predlast.first) {
                if (last.second > predlast.second) {
                    swap(US[US.size() - 1], US[US.size() - 2]);
                    US.pop_back();
                }
            }
        }
    }

    ImplicitSegmentTree ST(1e18 + 5);
    for (auto [w, c] : UF) {
        ST.change(w, max(c, ST.query(w, w)));
    }

    int ans = 0;
    for (auto [w, c] : US) {
        if (w <= MX) {
            ans = max(ans, c + ST.query(0, MX - w));
        }
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
