class Duval_decomposition {
public:
    Duval_decomposition(string s) {
        S = s;
        N = (int)s.size();
    }

    void build() {
        int i = 0;
        while (i < N) {
            int j = i + 1;
            int k = i;

            while (j < N && S[k] <= S[j]) {
                if (S[k] < S[j]) {
                    k = i;
                }
                else {
                    k++;
                }
                j++;
            }

            while (i <= k) {
                factorization.push_back(S.substr(i, j - k));
                i += j - k;
            }
        }
    }

    pair<string, int> min_cyclic_string() {
        int ans = 0;

        int i = 0;
        while (i < N) {
            ans = i;

            int j = i + 1;
            int k = i;

            while (j < 2 * N && S[k % N] <= S[j % N]) {
                if (S[k % N] < S[j % N]) {
                    k = i;
                }
                else {
                    k++;
                }
                j++;
            }

            while (i <= k) {
                i += j - k;
            }
        }

        return { S.substr(ans) + S.substr(0, ans), ans };
    }

    void print() {
        for (int i = 0; i < (int)factorization.size(); i++) {
            cout << factorization[i] << '\n';
        }
    }

private:
    string S;
    int N;

    vector<string> factorization;
};
