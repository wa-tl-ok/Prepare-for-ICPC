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

void Solve() {
    struct CAR {
        int l, r, id;
        bool operator<(const CAR& other) {
            return l < other.l;
        }
    };

    vector<int> ANS;

    int mx, b, f; cin >> mx >> b >> f;

    vector<int> Line(mx, 1); 
    vector<CAR> Cars;

    int Q; cin >> Q;
    for (int qq = 1; qq <= Q; qq++) {
        int type; cin >> type;

        if (type == 1) {
            int sz; cin >> sz; 

            bool F = 0;

            if (Cars.size() == 0) { // No cars
                int cur = 0;
                for (int i = 0; i < mx; i++) {
                    if (Line[i] == 1) {
                        ++cur;
                    }
                    else {
                        break;
                    }

                    if (cur == sz) {
                        int j = i;

                        while (cur > 0) {
                            Line[j] = 0;
                            --cur;

                            if (cur > 0) {
                                --j;
                            }
                        } Cars.push_back({ j, i, qq });

                        ANS.push_back(j); F = 1; break;
                    }
                }

                if (F == 0) {
                    ANS.push_back(-1);
                    F = 1;
                }
            }

            if (F == 0) { // Check First
                int cur = 0;
                for (int i = 0; i < mx; i++) {
                    if (Line[i] == 1) {
                        ++cur;
                    }
                    else {
                        break;
                    }

                    if (cur == sz + f) {
                        int j = i;

                        cur -= f;
                        j -= f;

                        while (cur > 0) {
                            Line[j] = 0;
                            --cur;

                            if (cur > 0) {
                                --j;
                            }
                        } Cars.push_back({ j, i - f, qq });

                        ANS.push_back(j); F = 1; break;
                    }
                }
            }
            
            if (F == 0) { // Check middle
                int cur = 0;
                for (int i = 0; i < mx; i++) {
                    if (Line[i] == 1) {
                        ++cur;
                    }
                    else {
                        cur = 0;
                    }

                    if (cur == sz + b + f) {
                        int j = i;

                        cur -= f;
                        j -= f;

                        while (cur > b) {
                            Line[j] = 0;
                            --cur;

                            if (cur > b) {
                                --j;
                            }
                        } Cars.push_back({ j, i - f, qq });

                        ANS.push_back(j); F = 1; break;
                    }
                }
            }

            if (F == 0) { // Check end
                int cur = 0;
                for (int i = Cars.back().r + 1; i < mx; i++) {
                    if (Line[i] == 1) {
                        ++cur;
                    }
                    else {
                        break;
                    }

                    if (cur == sz + b) {
                        int j = i;

                        while (cur > b) {
                            Line[j] = 0;
                            --cur;

                            if (cur > b) {
                                --j;
                            }
                        } Cars.push_back({ j, i, qq });

                        ANS.push_back(j); F = 1; break;
                    }
                }
            }

            if (F == 0) {
                ANS.push_back(-1);
            }
        }
        else {
            int id; cin >> id;

            vector<CAR> New_Cars;

            for (int i = 0; i < Cars.size(); i++) {
                if (Cars[i].id == id) {
                    for (int j = Cars[i].l; j <= Cars[i].r; j++) {
                        Line[j] = 1;
                    }
                }
                else {
                    New_Cars.push_back(Cars[i]);
                }
            }

            Cars = New_Cars;
        }

        if (Cars.size() > 0) {
            sort(Cars.begin(), Cars.end());
        }
    }

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
