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

struct DSU {
    vector<int> head;
    vector<int> rang;
 
    DSU(int n) {
        head.resize(n);
        for (int i = 0; i < n; i++) {
            head[i] = i;
        }
 
        rang.resize(n);
        for (int i = 0; i < n; i++) {
            rang[i] = 1;
        }
    }
 
    int Find(int x) {
        if (head[x] == x) {
            return x;
        }
        return head[x] = Find(head[x]);
    }
 
    bool Union(int x, int y) {
        x = Find(x);
        y = Find(y);
 
        if (x == y) {
            return false;
        }
 
        if (rang[x] > rang[y]) {
            swap(x, y);
        }
 
        head[x] = y;
 
        if (rang[x] == rang[y]) {
            ++rang[y];
        }
 
        return true;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}
