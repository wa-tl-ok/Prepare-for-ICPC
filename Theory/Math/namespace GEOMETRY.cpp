namespace GEOMETRY {
    template<typename T>
    struct r {
        T x;
        T y;

        r() {}
        r(T x_, T y_) : x(x_), y(y_) {}

        T len() const {
            return x * x + y * y;
        }

        long double sqrt_len() const {
            return sqrt(x * x + y * y);
        }

        r operator+(const r& a) const {
            return { x + a.x, y + a.y };
        }

        r operator-(const r& a) const {
            return { x - a.x, y - a.y };
        }

        template<typename G>
        r operator*(G k) const {
            return { x * k, y * k };
        }

        template<typename G>
        r operator/(G k) const {
            return { x / k, y / k };
        }

        r& operator+=(const r& a) {
            x += a.x; y += a.y;
            return *this;
        }

        r& operator-=(const r& a) {
            x -= a.x; y -= a.y;
            return *this;
        }

        template<typename G>
        r& operator*=(G k) {
            x *= k; y *= k;
            return *this;
        }

        template<typename G>
        r& operator/=(G k) {
            x /= k; y /= k;
            return *this;
        }

        T operator*(const r& a) const {
            return x * a.x + y * a.y;
        }

        T operator^(const r& a) const {
            return x * a.y - a.x * y;
        }

        bool operator==(const r& a) const {
            return x == a.x && y == a.y;
        }

        bool operator!=(const r& a) const {
            return !(*this == a);
        }

        bool operator<(const r& a) const {
            return len() < a.len();
        }

        bool operator>(const r& a) const {
            return a < *this;
        }

        bool operator<=(const r& a) const {
            return !(a < *this);
        }

        bool operator>=(const r& a) const {
            return !(*this < a);
        }
    };

    template<typename T>
    bool ccw(const r<T>& a, const r<T>& b, const r<T>& c) {
        return ((b - a) ^ (c - a)) > 0;
    }

    template<typename T>
    bool collinear(const r<T>& a, const r<T>& b, const r<T>& c) {
        return abs((b - a) ^ (c - a)) < eps;
    }

    template<typename T>
    istream& operator>>(istream& in, r<T>& p) {
        in >> p.x >> p.y;
        return in;
    }

    template<typename T>
    ostream& operator<<(ostream& out, const r<T>& p) {
        out << p.x << ' ' << p.y;
        return out;
    }

    template<typename T>
    vector<r<T>> get_env(vector<r<T>> points, bool F) {
        sort(points.begin(), points.end(), [](const r<T>& a, const r<T>& b) {
            return a.x < b.x || (a.x == b.x && a.y < b.y);
            });

        if (F == true) {
            // pass
        }
        else {
            reverse(all(points));
        }

        vector<r<T>> env;
        for (const auto& point : points) {
            while (env.size() >= 2 && ((env[env.size() - 1] - env[env.size() - 2]) ^ (point - env[env.size() - 2])) <= 0) {
                env.pop_back();
            }
            env.push_back(point);
        }
        return env;
    }

    template<typename T>
    vector<r<T>> convex_hull(vector<r<T>> points) {
        vector<r<T>> lower = get_env(points, true); lower.pop_back();
        vector<r<T>> upper = get_env(points, false); upper.pop_back();

        vector<r<T>> hull;
        for (const auto& point : lower) {
            hull.push_back(point);
        }
        for (const auto& point : upper) {
            hull.push_back(point);
        }

        return hull;
    }

    template<typename T>
    pair<r<T>, r<T>> tangents_from_point(const vector<r<T>>& hull, const r<T> P) {
        int n = hull.size();

        auto left_edge = [&](int i) {
            r<T> v1 = hull[i] - P;
            r<T> v2 = hull[(i + 1) % n] - P;
            return (v1 ^ v2) > 0;
            };

        int left_tangent = -1;
        {
            int low = 0, high = 2 * n;
            while (low < high) {
                int mid = (low + high) / 2;
                if (left_edge(mid % n)) {
                    low = mid + 1;
                }
                else {
                    high = mid;
                }
            }
            left_tangent = low % n;
        }

        auto right_edge = [&](int i) {
            r<T> v1 = hull[i] - P;
            r<T> v2 = hull[(i + 1) % n] - P;
            return (v1 ^ v2) >= 0;
            };

        int right_tangent = -1;
        {
            int low = 0, high = 2 * n;
            while (low < high) {
                int mid = (low + high) / 2;
                if (!right_edge(mid % n)) {
                    low = mid + 1;
                }
                else {
                    high = mid;
                }
            }
            right_tangent = low % n;
        }

        return { hull[right_tangent], hull[left_tangent] };
    }

    template<typename T>
    T convex_hull_diameter(const vector<r<T>>& hull) {
        int n = hull.size();

        auto sq_dist = [](const r<T>& a, const r<T>& b) {
            return (a - b).len();
            };

        T ans = 0;
        int r = 0;

        for (int l = 0; l < n; l++) {
            while (sq_dist(hull[l], hull[(r + 1) % n]) > sq_dist(hull[l], hull[r])) {
                r = (r + 1) % n;
            }
            ans = max(ans, sq_dist(hull[l], hull[r]));
        }

        return ans;
    }

    template<typename T>
    r<T> max_hull_point(const vector<r<T>>& hull, T A, T B) {
        int n = hull.size();

        if (n == 0) {
            return r<T>(0, 0);
        }

        if (n <= 30) {
            int best_index = 0;
            T best_val = A * hull[0].x + B * hull[0].y;
            for (int i = 1; i < n; i++) {
                T val = A * hull[i].x + B * hull[i].y;
                if (val > best_val) {
                    best_val = val;
                    best_index = i;
                }
            }
            return hull[best_index];
        }

        auto get_val = [&](int index) {
            return A * hull[index % n].x + B * hull[index % n].y;
            };

        int l = 0;
        int r = n - 1;

        while (r - l > 2) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;

            if (get_val(m1) < get_val(m2)) {
                l = m1;
            }
            else {
                r = m2;
            }
        }

        int best_index = l;
        T best_val = get_val(best_index);
        for (int i = l; i <= r; i++) {
            T val = get_val(i);
            if (val > best_val) {
                best_val = val;
                best_index = i;
            }
        }

        return hull[best_index];
    }

    template<typename T>
    struct l {
        T k;
        T b;

        l() {}
        l(T k_, T b_) : k(k_), b(b_) {}

        l operator+(const l& line) const {
            return { line.k + k, line.b + b };
        }

        l& operator+=(const l& line) {
            k += line.k; b += line.b;
            return *this;
        }

        l operator-(const l& line) const {
            return { k - line.k, b - line.b };
        }

        l& operator-=(const l& line) {
            k -= line.k; b -= line.b;
            return *this;
        }

        template<typename G>
        l operator*(G q) const {
            return { k * q, b * q };
        }

        template<typename G>
        l operator/(G q) const {
            return { k / q, b / q };
        }

        template<typename G>
        l& operator*=(G q) {
            k *= q; b *= q;
            return *this;
        }

        template<typename G>
        l& operator/=(G q) {
            k /= q; b /= q;
            return *this;
        }

        bool operator<(const l& line) const {
            return k < line.k;
        }

        T operator[](T x) const {
            return k * x + b;
        }
    };

    template<typename T, bool IsMin>
    class CHT {
    private:
        std::vector<l<T>> hull;
        std::vector<long double> crosses;
        T neutral;

        using Comp = std::conditional_t<IsMin, std::less<T>, std::greater<T>>;
        Comp comp;

        long double intersect(const l<T>& a, const l<T>& b) const {
            if (a.k == b.k) {
                if constexpr (IsMin) {
                    return a.b < b.b ? -1e18 : 1e18;
                }
                else {
                    return a.b > b.b ? -1e18 : 1e18;
                }
            }
            return static_cast<long double>(b.b - a.b) / (a.k - b.k);
        }

    public:
        explicit CHT(T neutral_ = std::numeric_limits<T>::max())
            : neutral(neutral_), comp(Comp()) {
        }

        void add_line(l<T> line) {
            while (hull.size() > 0 && hull.back().k == line.k) {
                if constexpr (IsMin) {
                    if (hull.back().b <= line.b) {
                        return;
                    }
                }
                else {
                    if (hull.back().b >= line.b) {
                        return;
                    }
                }

                hull.pop_back();

                if (crosses.size() > 0) {
                    crosses.pop_back();
                }
            }
            
            while (hull.size() > 0) {
                if (hull.size() == 1) {
                    crosses.push_back(intersect(hull.back(), line));
                    break;
                }

                long double nx = intersect(hull.back(), line);

                if (nx > crosses.back()) {
                    crosses.push_back(nx);
                    break;
                }
                else {
                    crosses.pop_back();
                    hull.pop_back();
                }
            }

            hull.push_back(line);
        }

        T query(T x) const {
            if (hull.empty()) {
                return neutral;
            }

            if (crosses.empty()) {
                return hull[0][x];
            }

            int i = crosses.size();

            int lo = 0;
            int hi = crosses.size() - 1;

            while (lo <= hi) {
                int mid = (lo + hi) / 2;

                if (x < crosses[mid]) {
                    i = mid;
                    hi = mid - 1;
                }
                else {
                    lo = mid + 1;
                }
            }

            return hull[i][x];
        }
    };

    template<typename T>
    using CHT_min = CHT<T, true>;

    template<typename T>
    using CHT_max = CHT<T, false>;

    template <typename T, typename Compare>
    class li_chao_tree {
    public:
        li_chao_tree(T low, T high, T neutral, Compare comp = Compare())
            : low_range(low), high_range(high), neutral(neutral), comp(comp), root(nullptr) {
        }

        void add_line(T k, T b) {
            l<T> l{ k, b };
            add_line(root, low_range, high_range, l);
        }

        T query(T x) {
            return query(root, low_range, high_range, x);
        }
    private:
        struct node {
            l<T> f;
            node* left = nullptr;
            node* right = nullptr;
            node(const l<T>& f_) : f(f_) {}
        };

        T low_range;
        T high_range;
        T neutral;
        Compare comp;
        node* root;

        void add_line(node*& v, T lo, T hi, l<T> f) {
            if (!v) {
                v = new node(f);
                return;
            }

            T mid = lo + (hi - lo) / 2;

            if (comp(f[mid], v->f[mid])) {
                std::swap(f, v->f);
            }

            if (lo == hi) {
                return;
            }

            if (comp(f[lo], v->f[lo])) {
                add_line(v->left, lo, mid, f);
            }
            else {
                add_line(v->right, mid + 1, hi, f);
            }
        }

        T query(node* v, T lo, T hi, T x) {
            if (!v) {
                return neutral;
            }

            T res = v->f[x];

            if (lo == hi) {
                return res;
            }

            T mid = lo + (hi - lo) / 2;

            if (x <= mid) {
                T candidate = query(v->left, lo, mid, x);
                return comp(res, candidate) ? res : candidate;
            }
            else {
                T candidate = query(v->right, mid + 1, hi, x);
                return comp(res, candidate) ? res : candidate;
            }
        }
    };

    template <typename T>
    using li_chao_tree_min = li_chao_tree<T, std::less<T>>;

    template <typename T>
    using li_chao_tree_max = li_chao_tree<T, std::greater<T>>;
}
