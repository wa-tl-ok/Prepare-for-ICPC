class Matrix {
public:
    Matrix(const vector<vector<int>>& matrix) : data(matrix) {}

    vector<vector<int>> getData() const {
        return data;
    }

    Matrix rotateclockwise() const {
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
};
