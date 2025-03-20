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
        int sum, maxsum, prefixsum, suffixsum;

        Node(int val) {
            sum = val;
            maxsum = val;
            prefixsum = val;
            suffixsum = val;
        }

        Node() { 
            sum = 0;
            maxsum = 0;
            prefixsum = 0;
            suffixsum = 0;
        }
    };

    SegmentTree(vector<int> Base) {
        int p = 1;
        while (p < (int)Base.size()) {
            p *= 2;
        }

        int q = Base.size();
        for (int i = 0; i < p - q; i++) {
            Base.push_back(0);
        }

        n = p;
        tree.resize(2 * n);

        for (int i = n; i < 2 * n; i++) {
            tree[i] = Node(Base[i - n]);
        }

        for (int i = n - 1; i >= 1; i--) {
            tree[i] = merge(tree[i * 2], tree[i * 2 + 1]);
        }
    }

    void plus(int pos, int x) {
        update(1, 0, n - 1, pos, x);
    }

    int get(int cl, int cr) {
        return query(1, 0, n - 1, cl, cr).maxsum;
    }

private:
    vector<Node> tree;
    int n;

    void update(int v, int l, int r, int pos, int x) {
        if (l == r) {
            tree[v] = Node(tree[v].sum + x);
            return;
        }

        int mid = (l + r) / 2;

        if (pos <= mid) {
            update(v * 2, l, mid, pos, x);
        }
        else {
            update(v * 2 + 1, mid + 1, r, pos, x);
        }

        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }

    Node query(int v, int l, int r, int cl, int cr) {
        if (r < cl || l > cr) {
            return Node(-1e9);
        }

        if (l >= cl && r <= cr) {
            return tree[v];
        }

        int mid = (l + r) / 2;

        Node Q1 = query(v * 2, l, mid, cl, cr);
        Node Q2 = query(v * 2 + 1, mid + 1, r, cl, cr);

        return merge(Q1, Q2);
    }

    Node merge(Node left, Node right) {
        Node M(0);
        M.sum = left.sum + right.sum;
        M.prefixsum = max(left.prefixsum, left.sum + right.prefixsum);
        M.suffixsum = max(right.suffixsum, left.suffixsum + right.sum);
        M.maxsum = max({ left.maxsum, right.maxsum, left.suffixsum + right.prefixsum });
        return M;
    }
};

struct Operation {
    int L;
    int R;
    int X;
    int ID;

    Operation(int L_, int R_, int X_, int ID_) {
        L = L_;
        R = R_;
        X = X_;
        ID = ID_;
    }
};

struct Query {
    int S;
    int T;
    int ID;

    Query(int S_, int T_, int ID_) {
        S = S_;
        T = T_;
        ID = ID_;
    }
};

void Solve() {
    int N, M; cin >> N >> M;

    map<int, vector<Operation>> Operations_with_R;
    map<int, vector<Operation>> Operations_with_L;

    vector<Operation> All_operations = { { -1, -1, -1, -1 } };
    for (int id = 1; id <= M; id++) {
        int L, R, X; cin >> L >> R >> X;
        All_operations.push_back({ L, R, X, id });

        Operations_with_R[R].push_back({ L, R, X, id });
        Operations_with_L[L].push_back({ L, R, X, id });
    }

    vector<int> Base(M + 1);
    for (int i = 0; i <= M; i++) {
        Base[i] = 0;
    }

    for (int id = 1; id <= M; id++) {
        int L = All_operations[id].L; int R = All_operations[id].R; int X = All_operations[id].X; int ID = All_operations[id].ID;
        if (L <= 1 && 1 <= R) {
            Base[id] = X;
        }
    }

    SegmentTree ST(Base);

    int Q; cin >> Q;
    vector<int> ANS(Q + 1);

    vector<vector<Query>> Queries_for_current_K(N + 1);
    for (int id = 1; id <= Q; id++) {
        int K, S, T; cin >> K >> S >> T;
        Queries_for_current_K[K].push_back({ S, T, id });
    }

    for (auto& Q : Queries_for_current_K[1]) {
        int S = Q.S; int T = Q.T; int ID = Q.ID;
        ANS[ID] = ST.get(S, T);
    }

    for (int K = 1; K < N; K++) {
        for (auto& Op : Operations_with_R[K]) {
            int L = Op.L; int R = Op.R; int X = Op.X; int ID = Op.ID;
            ST.plus(ID, -X); Base[ID] -= X;
        }

        for (auto& Op : Operations_with_L[K + 1]) {
            int L = Op.L; int R = Op.R; int X = Op.X; int ID = Op.ID;
            ST.plus(ID, X); Base[ID] += X;
        }

        for (auto& Q : Queries_for_current_K[K + 1]) {
            int S = Q.S; int T = Q.T; int ID = Q.ID;
            ANS[ID] = ST.get(S, T);
        }
    }

    for (int id = 1; id <= Q; id++) {
        cout << ANS[id] << '\n';
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
