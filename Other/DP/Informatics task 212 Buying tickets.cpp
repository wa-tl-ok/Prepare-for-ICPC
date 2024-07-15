//https://informatics.msk.ru/mod/statements/view.php?id=657&chapterid=212#1

#include <iostream> 
#include <iomanip> 
#include <algorithm> 
#include <cmath> 
#include <vector> 
#include <queue> 
#include <deque> 
#include <array> 
#include <list> 
#include <stack> 
#include <set> 
#include <unordered_set> 
#include <map> 
#include <unordered_map> 
#include <string> 
#include <cstring> 
#include <random> 
#include <bitset> 
#include <functional> 
#include <random> 

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    struct Trio {
        int a;
        int b;
        int c;
    };

    int n; cin >> n;
    vector<Trio> v;

    for (int i = 0; i < n; i++) {
        int p, q, l;
        cin >> p >> q >> l;

        v.push_back({ p, q, l });
    }

    vector<int> DP(n);

    DP[0] = v[0].a;
    if (n == 1) {
        cout << DP[0];
        return 0;
    }

    DP[1] = min(v[0].a + v[1].a, v[0].b);
    if (n == 2) {
        cout << DP[1];
        return 0;
    }

    DP[2] = min({ v[0].a + v[1].a + v[2].a, v[0].b + v[2].a, v[0].a + v[1].b, v[0].c });
    if (n == 3) {
        cout << DP[2];
        return 0;
    }

    for (int i = 3; i < n; i++) {
        DP[i] = min({ v[i].a + DP[i - 1], v[i - 1].b + DP[i - 2], v[i - 2].c + DP[i - 3] });
    }

    cout << DP[n - 1];
    return 0;
}
