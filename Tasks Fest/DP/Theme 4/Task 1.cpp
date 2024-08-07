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

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());

    vector<int> ans(n);
    ans[0] = a[1] - a[0];
    ans[1] = a[1] - a[0];

    for (int i = 2; i < n; i++) {
        ans[i] = min(ans[i - 2] + (a[i] - a[i - 1]), ans[i - 1] + (a[i] - a[i - 1]));
    }

    cout << ans[ans.size() - 1];

    return 0;
}
