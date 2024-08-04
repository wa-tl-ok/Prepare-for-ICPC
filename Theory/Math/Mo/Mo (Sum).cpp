class Mo {
public:
    Mo(const vector<int>& a) : a(a) {
        n = a.size();
        block_size = sqrt(n);
        answers.resize(0);
    }

    void add_query(int l, int r) {
        queries.push_back({ l, r, (int)queries.size() });
    }

    vector<int> get_answer() {
        sort(queries.begin(), queries.end(), [this](const Query& q1, const Query& q2) {
            if (q1.l / block_size != q2.l / block_size)
                return q1.l / block_size < q2.l / block_size;
            return q1.r < q2.r;
            });

        current_l = 0;
        current_r = -1;
        current_sum = 0;

        answers.resize(queries.size());

        for (const auto& query : queries) {
            while (current_r < query.r) {
                add(a[++current_r]);
            }
            while (current_r > query.r) {
                remove(a[current_r--]);
            }
            while (current_l < query.l) {
                remove(a[current_l++]);
            }
            while (current_l > query.l) {
                add(a[--current_l]);
            }
            answers[query.id] = current_sum;
        }

        return answers;
    }

private:
    struct Query {
        int l, r, id;
    };

    vector<int> a;
    vector<Query> queries;
    vector<int> answers;

    int n;
    int block_size;
    int current_l, current_r;
    int current_sum;

    void add(int x) {
        current_sum += x;
    }

    void remove(int x) {
        current_sum -= x;
    }
};
