#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <deque>
#include <array>
#include <list>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <string>
#include <cstring>
#include <random>
#include <bitset>
#include <stdexcept>
#include <cassert>

using namespace std;

class Matrix {
public:
    Matrix(const vector<vector<int>>& matrix) : data(matrix) {}

    vector<vector<int>> getData() const {
        return data;
    }

    Matrix transpose() const {
        vector<vector<int>> transposed_matrix(data[0].size(), vector<int>(data.size(), 0));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                transposed_matrix[j][i] = data[i][j];
            }
        }
        return Matrix(transposed_matrix);
    }

    Matrix rotateClockwise() const {
        vector<vector<int>> rotated_matrix(data[0].size(), vector<int>(data.size(), 0));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                rotated_matrix[j][data.size() - 1 - i] = data[i][j];
            }
        }

        return Matrix(rotated_matrix);
    }

    Matrix add(const Matrix& other) const {
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
            throw invalid_argument("Matrices dimensions do not match for addition.");
        }

        vector<vector<int>> result_matrix(data.size(), vector<int>(data[0].size(), 0));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result_matrix[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return Matrix(result_matrix);
    }

    Matrix multiply(const Matrix& other) const {
        size_t rows1 = data.size();
        size_t columns1 = data[0].size();
        size_t rows2 = other.data.size();
        size_t columns2 = other.data[0].size();

        if (columns1 != rows2) {
            throw invalid_argument("Matrices dimensions do not match for multiplication.");
        }

        vector<vector<int>> result_matrix(rows1, vector<int>(columns2, 0));
        for (size_t i = 0; i < rows1; ++i) {
            for (size_t j = 0; j < columns2; ++j) {
                for (size_t k = 0; k < columns1; ++k) {
                    result_matrix[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }

        return Matrix(result_matrix);
    }

    void print() const {
        for (const auto& row : data) {
            for (const auto& elem : row) {
                cout << elem << " ";
            }
            cout << endl;
        }
    }
private:
    vector<vector<int>> data;
};

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    vector<vector<int>> matrix1 = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    vector<vector<int>> matrix2 = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    Matrix mat1(matrix1);
    Matrix mat2(matrix2);

    // Test transpose
    Matrix transposed = mat1.transpose();
    vector<vector<int>> expected_transpose = {
        {1, 4, 7},
        {2, 5, 8},
        {3, 6, 9}
    };
    assert(transposed.getData() == expected_transpose);

    // Test rotate clockwise
    Matrix rotated = mat1.rotateClockwise();
    vector<vector<int>> expected_rotation = {
        {7, 4, 1},
        {8, 5, 2},
        {9, 6, 3}
    };
    assert(rotated.getData() == expected_rotation);

    // Test addition
    Matrix added = mat1.add(mat2);
    vector<vector<int>> expected_addition = {
        {10, 10, 10},
        {10, 10, 10},
        {10, 10, 10}
    };
    assert(added.getData() == expected_addition);

    // Test multiplication
    Matrix multiplied = mat1.multiply(mat2);
    vector<vector<int>> expected_multiplication = {
        {30, 24, 18},
        {84, 69, 54},
        {138, 114, 90}
    };
    assert(multiplied.getData() == expected_multiplication);

    return 0;
}
