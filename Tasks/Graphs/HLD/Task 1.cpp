//https://atcoder.jp/contests/abc368/tasks/abc368_d

void Solve() {
    int n; cin >> n;
    int k; cin >> k;

    TREE g(n);

    for (int i = 0; i < n - 1; i++) {
        int u, v; cin >> u >> v;
        --u;
        --v;
        g.Add_edge(u, v);
    }

    vector<int> Upd(k);
    for (int i = 0; i < k; i++) {
        cin >> Upd[i];
        Upd[i] -= 1;
    }

    g.plus(Upd[0], 1);
    for (int i = 1; i < k; i++) {
        g.plus(Upd[0], Upd[i], 1);
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (g.Get_sum(i, i) > 0) {
            ++ans;
        }
    }

    cout << ans;
}
