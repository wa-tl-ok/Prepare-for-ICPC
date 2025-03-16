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

void Solve() {
    int c; cin >> c;

    int left = 1;
    int right = c;

    for (int i = 0; i < 10; i++) {
        if (left == right || left + 1 == right) {
            break;
        }

        int n = (right - left + 1) / 3;
        if (3 * n + 2 <= right - left + 1) {
            ++n;
        }

        vector<int> left_eggs;
        vector<int> middle_eggs;
        vector<int> right_eggs;

        for (int j = left; j < left + n; j++) {
            left_eggs.push_back(j);
        }
        for (int j = left + n; j < left + 2 * n; j++) {
            middle_eggs.push_back(j);
        }
        for (int j = left + 2 * n; j <= right; j++) {
            right_eggs.push_back(j);
        }

        cout << "? " << n << " " << n << endl;
        for (int egg : left_eggs) {
            cout << egg << " ";
        }
        cout << endl;
        for (int egg : middle_eggs) {
            cout << egg << " ";
        }
        cout << endl;

        string ans;
        cin >> ans;

        if (ans == ">") {
            right = left + n - 1;
        }
        else if (ans == "=") {
            left = left + 2 * n;
        }
        else if (ans == "<") {
            right = left + 2 * n - 1;
            left = left + n;
        }
    }

    if (left == right) {
        cout << "! " << left << endl;
    }
    else if (left + 1 == right) {
        cout << "? " << 1 << " " << 1 << endl;
        cout << left << endl;
        cout << right << endl;

        string ans;
        cin >> ans;

        if (ans == ">") {
            cout << "! " << left << endl;
        }
        else {
            cout << "! " << right << endl;
        }
    }
    else {
        assert(false);
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
