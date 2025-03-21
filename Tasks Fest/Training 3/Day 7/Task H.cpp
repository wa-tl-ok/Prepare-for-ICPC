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

struct Bitwise_trie {
    struct TrieNode {
        int count;
        TrieNode* children[2];
        TrieNode* parent;

        TrieNode() : count(0), parent(nullptr) {
            children[0] = nullptr;
            children[1] = nullptr;
        }
    };

    Bitwise_trie() {
        root = new TrieNode();
    }

    void add(int num) {
        TrieNode* current = root;
        current->count++;

        for (int i = 31; i >= 0; i--) {
            bool bit = (num >> i) & 1;

            if (current->children[bit] == nullptr) {
                current->children[bit] = new TrieNode();
                current->children[bit]->parent = current;
            }

            current = current->children[bit];
            current->count++;
        }
    }

    int query(int num) {
        TrieNode* current = root;
        int maxXOR = 0;

        for (int i = 31; i >= 0; i--) {
            bool bit = (num >> i) & 1;
            bool oppositeBit = !bit;

            if (current->children[oppositeBit] != nullptr) {
                maxXOR |= (1 << i);
                current = current->children[oppositeBit];
            }
            else {
                current = current->children[bit];
            }
        }

        return maxXOR;
    }

    TrieNode* root;
};

void Solve() {
    int n; cin >> n;
    vector<int> a(n - 1);
    for (int i = 0; i < n - 1; i++) {
        cin >> a[i];
    }

    vector<int> c(n);
    c[0] = 0;
    for (int i = 1; i < n; i++) {
        c[i] = c[i - 1] ^ a[i - 1];
    }

    Bitwise_trie T;

    for (int i = 0; i < n; i++) {
        T.add(c[i]);
    }

    for (int b0 = 0; b0 <= n - 1; b0++) {
        if (T.query(b0) < n) {
            vector<int> ans;
            for (int i = 0; i < n; i++) {
                ans.push_back(b0 ^ c[i]);
            }

            set<int> s;
            for (int i = 0; i < n; i++) {
                s.insert(b0 ^ c[i]);
            }

            if (s.size() == n) {
                PRINT(ans);
            }

            return;
        }
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
