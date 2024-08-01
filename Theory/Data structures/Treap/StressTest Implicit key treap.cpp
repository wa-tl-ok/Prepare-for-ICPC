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

void Go() {
    l = R(0, a.size() - 1);
    r = R(0, a.size() - 1);
    if (l > r) {
        swap(l, r);
    }
}

void Test_query() {
    Go();

    assert(Sum(l, r) == t.Sum(l, r));
    assert(Min(l, r) == t.Min(l, r));
    assert(Max(l, r) == t.Max(l, r));
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

int main() {
    for (int i = 1; i <= 1000; i++) {
        t.Add(-1, i);
        a.push_back(i);
    }

    Basic_test();

    Rev_test();

    Upd_test();

    Plus_test();

    RangeAdd_test();

    RangeSet_test();

    cout << "OK" << endl;

    return 0;
}
