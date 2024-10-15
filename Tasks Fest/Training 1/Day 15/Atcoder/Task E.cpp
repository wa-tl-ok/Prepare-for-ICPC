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

#define int long long

struct Node {
    map<int, Node*> children;
    Node* parent;
    int ans;

    Node(int x, Node* p) : ans(x), parent(p) {}
};

void Solve() {
    vector<int> ANS;

    Node* node = new Node(-1, nullptr);
    map<int, Node*> List;

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        string q; cin >> q;

        if (q == "ADD") {
            int x; cin >> x;

            if (node->children.find(x) == node->children.end()) {
                node->children[x] = new Node(x, node);
            }
            
            node = node->children[x];
        }
        else if (q == "DELETE") {
            if (node->parent != nullptr) {
                node = node->parent;
            }
        }
        else if (q == "SAVE") {
            int y; cin >> y;
            List[y] = node;
        }
        else {
            int z; cin >> z;
            
            if (List.find(z) != List.end()) {
                node = List[z];
            }
            else {
                while (node->parent != nullptr) {
                    node = node->parent;
                }
            }
        }

        ANS.push_back(node->ans);
    }

    for (auto p : ANS) {
        cout << p << ' ';
    }
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

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

    return 0;
}
