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

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b; 
        b = a % b; 
        a = temp;
    }
    return a;
}

int mathnod(int a, int b) { 
    return gcd(a, b); 
}

int mathnok(int a, int b) { 
    return a * b / mathnod(a, b); 
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}
