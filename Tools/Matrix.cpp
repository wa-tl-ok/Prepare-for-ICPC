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

vector<vector<int>> transp(vector<vector<int>>& Matrix) {
    vector<vector<int>> transposed_matrix(Matrix[0].size(), vector<int>(Matrix.size(), 0));
    for (size_t i = 0; i < Matrix.size(); ++i) {
        for (size_t j = 0; j < Matrix[0].size(); ++j) {
            transposed_matrix[j][i] = Matrix[i][j];
        }
    }
    return transposed_matrix;
}

vector<vector<int>> rotate_clockwise(vector<vector<int>>& Matrix) {
    vector<vector<int>> rotated_matrix(Matrix[0].size(), vector<int>(Matrix.size(), 0));
    for (size_t i = 0; i < Matrix.size(); ++i) {
        for (size_t j = 0; j < Matrix[0].size(); ++j) {
            rotated_matrix[j][Matrix.size() - 1 - i] = Matrix[i][j];
        }
    }
    return rotated_matrix;
}

vector<vector<int>> plus_matrix(vector<vector<int>>& Matrix1, vector<vector<int>>& Matrix2) {
    vector<vector<int>> result_matrix(Matrix1.size(), vector<int>(Matrix1[0].size(), 0));
    for (size_t i = 0; i < Matrix1.size(); ++i) {
        for (size_t j = 0; j < Matrix1[0].size(); ++j) {
            result_matrix[i][j] = Matrix1[i][j] + Matrix2[i][j];
        }
    }
    return result_matrix;
}

vector<vector<int>> multiply_matrix(vector<vector<int>>& Matrix1, vector<vector<int>>& Matrix2) {
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    return 0;
}
