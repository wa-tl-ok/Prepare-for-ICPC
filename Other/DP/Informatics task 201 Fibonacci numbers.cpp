//https://informatics.msk.ru/mod/statements/view.php?chapterid=201#1

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

vector<vector<int>> multiply_matrix(const vector<vector<int>>& Matrix1, const vector<vector<int>>& Matrix2) {
    size_t rows1 = Matrix1.size();
    size_t columns1 = Matrix1[0].size();
    size_t rows2 = Matrix2.size();
    size_t columns2 = Matrix2[0].size();
    if (columns1 != rows2) {
        throw invalid_argument("Wrong!");
    }
    vector<vector<int>> result_matrix(rows1, vector<int>(columns2, 0));
    for (size_t i = 0; i < rows1; ++i) {
        for (size_t j = 0; j < columns2; ++j) {
            for (size_t k = 0; k < columns1; ++k) {
                result_matrix[i][j] += Matrix1[i][k] * Matrix2[k][j];
            }
        }
    }
    return result_matrix;
}

vector<vector<int>> Fast_power(vector<vector<int>> A, int n) {
    vector<vector<int>> result = { {1, 0}, {0, 1} };

    while (n > 0) {
        if (n % 2 == 1) {
            result = multiply_matrix(result, A);
        }
        A = multiply_matrix(A, A);
        n /= 2;
    }

    return result;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int n; cin >> n;

    vector<vector<int>> A = { {0, 1}, {1, 1} };
    vector<vector<int>> result = Fast_power(A, n - 1);

    cout << result[1][1];

    return 0;
}
