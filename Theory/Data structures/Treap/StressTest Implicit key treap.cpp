int R(int l, int r) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(l, r);
    return dis(gen);
}

vector<int> a;
Treap t;
int l, r;

int Min(int l, int r) {
    int minValue = a[l];
    for (int i = l + 1; i <= r; ++i) {
        if (a[i] < minValue) {
            minValue = a[i];
        }
    }
    return minValue;
}

int Max(int l, int r) {
    int maxValue = a[l];
    for (int i = l + 1; i <= r; ++i) {
        if (a[i] > maxValue) {
            maxValue = a[i];
        }
    }
    return maxValue;
}

int Sum(int l, int r) {
    int sumValue = 0;
    for (int i = l; i <= r; ++i) {
        sumValue += a[i];
    }
    return sumValue;
}

void Rev(int l, int r) {
    while (l < r) {
        swap(a[l], a[r]);
        ++l;
        --r;
    }
}

void Upd(int pos, int x) {
    a[pos] = x;
}

void Plus(int pos, int x) {
    a[pos] += x;
}

void RangeAdd(int l, int r, int x) {
    for (int i = l; i <= r; ++i) {
        a[i] += x;
    }
}

void RangeSet(int l, int r, int x) {
    for (int i = l; i <= r; ++i) {
        a[i] = x;
    }
}

void Del(int pos) {
    vector<int> b;
    for (int i = 0; i < (int)a.size(); i++) {
        if (i != pos) {
            b.push_back(a[i]);
        }
    }
    a.clear();
    for (auto t : b) {
        a.push_back(t);
    }
}

void Go() {
    l = R(0, a.size() - 1);
    r = R(0, a.size() - 1);
    if (l > r) {
        swap(l, r);
    }
}

void Test_query() {
    Go();

    int sum_a = Sum(l, r);
    int sum_t = t.Sum(l, r);
    int min_a = Min(l, r);
    int min_t = t.Min(l, r);
    int max_a = Max(l, r);
    int max_t = t.Max(l, r);

    if (sum_a != sum_t) {
        cout << "Error: Sum mismatch!\n";
        cout << "Expected Sum: " << sum_t << ", Actual Sum: " << sum_a << "\n";
        cout << "Range: [" << l << ", " << r << "]\n";
        
        t.Print();
        for (auto w : a) {
            cout << w << ' ';
        } cout << endl;

        assert(false);
    }

    if (min_a != min_t) {
        cout << "Error: Min mismatch!\n";
        cout << "Expected Min: " << min_t << ", Actual Min: " << min_a << "\n";
        cout << "Range: [" << l << ", " << r << "]\n";
        
        t.Print();
        for (auto w : a) {
            cout << w << ' ';
        } cout << endl;

        assert(false);
    }

    if (max_a != max_t) {
        cout << "Error: Max mismatch!\n";
        cout << "Expected Max: " << max_t << ", Actual Max: " << max_a << "\n";
        cout << "Range: [" << l << ", " << r << "]\n";
        
        t.Print();
        for (auto w : a) {
            cout << w << ' ';
        } cout << endl;

        assert(false);
    }
}

void Basic_test() {
    for (int i = 0; i < t.Size(); i++) {
        l = i;
        r = i;
        Test_query();
    }
    for (int i = 0; i < 1000; i++) {
        Test_query();
    }
}

void Rev_test() {
    for (int i = 0; i < 1000; i++) {
        Go();

        Rev(l, r);
        t.Rev(l, r);

        Test_query();
    }
}

void Upd_test() {
    for (int i = 0; i < 1000; i++) {
        int x = R(0, 100);
        int pos = R(0, t.Size() - 1);

        Upd(pos, x);
        t.Upd(pos, x);

        Test_query();
    }
}

void Plus_test() {
    for (int i = 0; i < 1000; i++) {
        int x = R(0, 100);
        int pos = R(0, t.Size() - 1);

        Plus(pos, x);
        t.Plus(pos, x);

        Test_query();
    }
}

void RangeAdd_test() {
    for (int i = 0; i < 1000; i++) {
        int x = R(0, 100);
        Go();

        RangeAdd(l, r, x);
        t.RangeAdd(l, r, x);

        Test_query();
    }
}

void RangeSet_test() {
    for (int i = 0; i < 1000; i++) {
        int x = R(0, 100);
        Go();

        RangeSet(l, r, x);
        t.RangeSet(l, r, x);

        Test_query();
    }
}

void Del_test() {
    int e = t.Size();

    for (int i = 0; i < e - 1; i++) {
        int pos = R(0, t.Size() - 1);

        Del(pos);
        t.Del(pos);

        Test_query();
    }

    Del(0);
    t.Del(0);
}

void StressTest() {
    const int numOperations = 1000;
    vector<pair<int, int>> operations(numOperations);

    for (int i = 0; i < numOperations; ++i) {
        int opType = R(0, 5);
        int x = R(0, 100);
        int pos = R(0, t.Size() - 1);
        int pos2 = R(pos, t.Size() - 1);

        operations[i] = { opType, x };

        switch (opType) {
        case 0:  // Upd
            Upd(pos, x);
            t.Upd(pos, x);
            break;
        case 1:  // Plus
            Plus(pos, x);
            t.Plus(pos, x);
            break;
        case 2:  // RangeAdd
            RangeAdd(pos, pos2, x);
            t.RangeAdd(pos, pos2, x);
            break;
        case 3:  // RangeSet
            RangeSet(pos, pos2, x);
            t.RangeSet(pos, pos2, x);
            break;
        case 4:  // Rev
            Rev(pos, pos2);
            t.Rev(pos, pos2);
            break;
        case 5:  // Del
            Del(pos);
            t.Del(pos);
            break;
        }

        if (i % 1000 == 0) {
            for (int j = 0; j < 10; ++j) {
                Go();
                Test_query();
            }
        }
    }
}

signed main() {
    for (int q = 0; q < 10; q++) {
        int pos1 = R(0, 100);
        int pos2 = R(pos1, 1000);

        for (int i = pos1; i <= pos2; i++) {
            t.Add(-1, i);
            a.push_back(i);
        }

        Basic_test();

        Rev_test();

        Upd_test();

        Plus_test();

        RangeAdd_test();

        RangeSet_test();

        Del_test();
    }

    for (int q = 0; q < 1000; q++) {
        for (int i = 1; i <= 1000; i++) {
            a.push_back(i);
            t.Add(-1, i);
        }

        StressTest();

        while (a.size() > 0) {
            Del(0);
            t.Del(0);
        }
    }

    cout << "OK" << endl;

    return 0;
}
