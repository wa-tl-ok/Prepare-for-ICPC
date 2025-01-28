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

    Matrix operator+(const Matrix& other) const {
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

    Matrix operator-(const Matrix& other) const {
        if (data.size() != other.data.size() || data[0].size() != other.data[0].size()) {
            throw invalid_argument("Matrices dimensions do not match for subtraction.");
        }

        vector<vector<int>> result_matrix(data.size(), vector<int>(data[0].size(), 0));
        for (size_t i = 0; i < data.size(); ++i) {
            for (size_t j = 0; j < data[0].size(); ++j) {
                result_matrix[i][j] = data[i][j] - other.data[i][j];
            }
        }

        return Matrix(result_matrix);
    }

    Matrix operator*(const Matrix& other) const {
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

    Matrix operator/(const Matrix& other) const {
        return *this * other.inverse();
    }

    bool operator==(const Matrix& other) const {
        return data == other.data;
    }

    bool operator!=(const Matrix& other) const {
        return !(*this == other);
    }

    Matrix pow(int n) const {
        if (data.size() != data[0].size()) {
            throw invalid_argument("Matrix must be square for exponentiation.");
        }

        Matrix result = identity(data.size());
        Matrix base = *this;

        while (n > 0) {
            if (n % 2 == 1) {
                result = result * base;
            }
            base = base * base;
            n /= 2;
        }

        return result;
    }

    int determinant() const {
        size_t n = data.size();
        if (n == 0) {
            throw invalid_argument("Determinant is not defined for an empty matrix.");
        }
        if (n != data[0].size()) {
            throw invalid_argument("Determinant is defined only for square matrices.");
        }

        if (n == 1) {
            return data[0][0];
        }
        if (n == 2) {
            return data[0][0] * data[1][1] - data[0][1] * data[1][0];
        }

        int det = 0;
        for (size_t j = 0; j < n; ++j) {
            det += (j % 2 == 0 ? 1 : -1) * data[0][j] * minor(0, j).determinant();
        }
        return det;
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

    static Matrix identity(size_t size) {
        vector<vector<int>> identity_matrix(size, vector<int>(size, 0));
        for (size_t i = 0; i < size; ++i) {
            identity_matrix[i][i] = 1;
        }
        return Matrix(identity_matrix);
    }

    static Matrix identity(size_t size) {
        vector<vector<int>> identity_matrix(size, vector<int>(size, 0));
        for (size_t i = 0; i < size; ++i) {
            identity_matrix[i][i] = 1;
        }
        return Matrix(identity_matrix);
    }

    Matrix inverse() const {
        size_t n = data.size();
        vector<vector<int>> augmented_matrix(n, vector<int>(2 * n, 0));

        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                augmented_matrix[i][j] = data[i][j];
            }
            augmented_matrix[i][i + n] = 1;
        }

        for (size_t i = 0; i < n; ++i) {
            if (augmented_matrix[i][i] == 0) {
                throw invalid_argument("Matrix is singular and cannot be inverted.");
            }

            int pivot = augmented_matrix[i][i];
            for (size_t j = 0; j < 2 * n; ++j) {
                augmented_matrix[i][j] /= pivot;
            }

            for (size_t j = 0; j < n; ++j) {
                if (j != i) {
                    int factor = augmented_matrix[j][i];
                    for (size_t k = 0; k < 2 * n; ++k) {
                        augmented_matrix[j][k] -= factor * augmented_matrix[i][k];
                    }
                }
            }
        }

        vector<vector<int>> inverse_matrix(n, vector<int>(n, 0));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j) {
                inverse_matrix[i][j] = augmented_matrix[i][j + n];
            }
        }

        return Matrix(inverse_matrix);
    }

    Matrix minor(size_t row, size_t col) const {
        vector<vector<int>> minor_matrix;
        for (size_t i = 0; i < data.size(); ++i) {
            if (i != row) {
                vector<int> new_row;
                for (size_t j = 0; j < data[i].size(); ++j) {
                    if (j != col) {
                        new_row.push_back(data[i][j]);
                    }
                }
                minor_matrix.push_back(new_row);
            }
        }
        return Matrix(minor_matrix);
    }
};
