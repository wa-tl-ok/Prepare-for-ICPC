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

int bs_rr(vector<pair<int, int>>& arr, int target) {
    /*
        Find min index of number that > target
    */
    if (arr[arr.size() - 1].first <= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid].first <= target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

void Solve() {
    vector<Int> ANS;

    int n, q; cin >> n >> q;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> b(n);
    for (int j = 0; j < n; j++) {
        cin >> b[j];
    }

    vector<pair<int, int>> ai;
    for (int i = 0; i < n; i++) {
        ai.push_back({ a[i], i });
    }

    sort(ai.begin(), ai.end());

    vector<pair<int, int>> bj;
    for (int j = 0; j < n; j++) {
        bj.push_back({ b[j], j });
    }

    sort(bj.begin(), bj.end());

    map<int, int> id_a;
    for (int i = 0; i < n; i++) {
        id_a[ai[i].second] = i;
    }

    map<int, int> id_b;
    for (int j = 0; j < n; j++) {
        id_b[bj[j].second] = j;
    }

    Int ans = 1;
    for (int ij = 0; ij < n; ij++) {
        ans *= min(ai[ij].first, bj[ij].first);
    }

    ANS.push_back(ans);

    //cout << "new ans ---> " << ans << '\n';

    for (int qq = 1; qq <= q; qq++) {
        int o; cin >> o;
        int x; cin >> x;
        --x;

        if (o == 1) {
            int i = id_a[x];
            ai[i].first += 1;

            if (i == n - 1) {
                //cout << "new ans ---> " << ans << " / " << min(ai[i].first - 1, bj[i].first) << " * " << min(ai[i].first, bj[i].first);

                ans /= min(ai[i].first - 1, bj[i].first);
                ans *= min(ai[i].first, bj[i].first);

                //cout << " = " << ans << '\n';
            }
            else if (ai[i].first <= ai[i + 1].first) {
                //cout << "new ans ---> " << ans << " / " << min(ai[i].first - 1, bj[i].first) << " * " << min(ai[i].first, bj[i].first);

                ans /= min(ai[i].first - 1, bj[i].first);
                ans *= min(ai[i].first, bj[i].first);

                //cout << " = " << ans << '\n';
            }
            else {
                ai[i].first -= 1;
                int id_swap = bs_rr(ai, ai[i].first);
                ai[i].first += 1;

                int l = -1;
                int r = -1;

                if (id_swap == -1) {
                    l = i;
                    r = n - 1;
                }
                else {
                    l = i;
                    r = id_swap - 1;
                }

                //cout << "new ans ---> " << ans;

                ans /= min(ai[l].first - 1, bj[l].first);

                //cout << " / " << min(ai[l].first - 1, bj[l].first);

                ans /= min(ai[r].first, bj[r].first);

                //cout << " / " << min(ai[r].first, bj[r].first);

                swap(ai[l], ai[r]);

                ans *= min(ai[l].first, bj[l].first);

                //cout << " * " << min(ai[l].first, bj[l].first);

                ans *= min(ai[r].first, bj[r].first);

                //cout << " * " << min(ai[r].first, bj[r].first);

                id_a[ai[l].second] = l;
                id_a[ai[r].second] = r;

                //cout << " = " << ans;

                //cout << '\n';
            }
        }
        else {
            int j = id_b[x];
            bj[j].first += 1;

            if (j == n - 1) {
                //cout << "new ans ---> " << ans << " / " << min(ai[j].first, bj[j].first - 1) << " * " << min(ai[j].first, bj[j].first);

                ans /= min(ai[j].first, bj[j].first - 1);
                ans *= min(ai[j].first, bj[j].first);

                //cout << " = " << ans << '\n';
            }
            else if (bj[j].first <= bj[j + 1].first) {
                //cout << "new ans ---> " << ans << " / " << min(ai[j].first, bj[j].first - 1) << " * " << min(ai[j].first, bj[j].first);

                ans /= min(ai[j].first, bj[j].first - 1);
                ans *= min(ai[j].first, bj[j].first);

                //cout << " = " << ans << '\n';
            }
            else {
                bj[j].first -= 1;
                int id_swap = bs_rr(bj, bj[j].first);
                bj[j].first += 1;

                int l = -1;
                int r = -1;

                if (id_swap == -1) {
                    l = j;
                    r = n - 1;
                }
                else {
                    l = j;
                    r = id_swap - 1;
                }

                //cout << "new ans ---> " << ans;

                ans /= min(ai[l].first, bj[l].first - 1);

                //cout << " / " << min(ai[l].first, bj[l].first - 1);

                ans /= min(ai[r].first, bj[r].first);

                //cout << " / " << min(ai[r].first, bj[r].first);
                     
                swap(bj[l], bj[r]);

                ans *= min(ai[l].first, bj[l].first);

                //cout << " * " << min(ai[l].first, bj[l].first);

                ans *= min(ai[r].first, bj[r].first);

                //cout << " * " << min(ai[r].first, bj[r].first);

                id_b[bj[l].second] = l;
                id_b[bj[r].second] = r;

                //cout << " = " << ans;

                //cout << '\n';
            }
        }

        /*cout << "new ai, bj:\n";

        cout << "ai: ";
        for (int i = 0; i < n; i++) {
            cout << ai[i].first << ' ';
        } 
        cout << '\n';

        cout << "bj: ";
        for (int j = 0; j < n; j++) {
            cout << bj[j].first << ' ';
        } 
        cout << '\n';*/

        ANS.push_back(ans);
    }

    //cout << "TASK ANSWER ------------------------------> ";

    PRINT(ANS);
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
