//https://informatics.msk.ru/mod/statements/view.php?id=33342&chapterid=745#1

#include <iostream>
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

using ll = long long;
using str = string;

ll mod = 1e9 + 7;
char type; str s;
vector<ll> step(11);
map<ll, bool> m;

int main() {
    type = '!';

    step[0] = 1;
    for (int i = 1; i < 11; ++i) {
        step[i] = step[i - 1] * 31;
        step[i] %= mod;
    }

    while (true) {
        cin >> type;

        if (type == '#') {
            break;
        }

        cin >> s;

        ll Hash = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            Hash += step[i] * (s[i] - 'a' + 1);
            Hash %= mod;
        }

        if (type == '-') {
            m[Hash] = false;
        }
        else if (type == '+') {
            m[Hash] = true;
        }
        else {
            if (m[Hash] == true) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
        }
    }
}
