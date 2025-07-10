struct Point_KD {
    double x;
    double y;
    int index;

    Point_KD() : x(0), y(0), index(-1) {}
    Point_KD(double x, double y, int index = -1) : x(x), y(y), index(index) {}
};

double dist(const Point_KD& a, const Point_KD& b) {
    return sqrtl((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}

Point_KD rotate(const Point_KD& p, double theta_rad) {
    return Point_KD(p.x * cos(theta_rad) - p.y * sin(theta_rad), p.x * sin(theta_rad) + p.y * cos(theta_rad), p.index);
}

struct BBox {
    double x_min;
    double x_max;
    double y_min;
    double y_max;

    BBox() : x_min(1e18), x_max(-1e18), y_min(1e18), y_max(-1e18) {}

    void update(const Point_KD& p) {
        x_min = min(x_min, p.x);
        x_max = max(x_max, p.x);
        y_min = min(y_min, p.y);
        y_max = max(y_max, p.y);
    }

    void update(const BBox& b) {
        x_min = min(x_min, b.x_min);
        x_max = max(x_max, b.x_max);
        y_min = min(y_min, b.y_min);
        y_max = max(y_max, b.y_max);
    }

    double min_dist_to_point(const Point_KD& p) const {
        double dx = 0.0;

        if (p.x < x_min) {
            dx = x_min - p.x;
        }

        if (p.x > x_max) {
            dx = p.x - x_max;
        }

        double dy = 0.0;

        if (p.y < y_min) {
            dy = y_min - p.y;
        }

        if (p.y > y_max) {
            dy = p.y - y_max;
        }

        return sqrtl(dx * dx + dy * dy);
    }
};

struct KDNode {
    Point_KD point;
    BBox bbox;
    KDNode* left;
    KDNode* right;

    KDNode(const Point_KD& p) : point(p), left(nullptr), right(nullptr) {
        bbox.update(p);
    }

    ~KDNode() {
        delete left;
        delete right;
    }

    void update_bbox() {
        bbox = BBox();
        bbox.update(point);
        if (left) {
            bbox.update(left->bbox);
        }
        if (right) {
            bbox.update(right->bbox);
        }
    }
};

class KDTree {
public:
    KDTree() : root(nullptr) {}

    ~KDTree() { delete root; }

    void build(vector<Point_KD> points) {
        root = build(points, 0, (int)points.size(), 0);
    }

    Point_KD Find_Nearest_In_Cone(const Point_KD& p, const vector<Point_KD>& a) {
        double best_dist = 1e18; Point_KD best_point;
        search(root, p, a, 0, best_dist, best_point);
        return best_point;
    }

private:
    KDNode* root;
    const double tg_KD = sqrtl(3);
    const double eps_KD = 1e-18;

    KDNode* build(vector<Point_KD>& points, int l, int r, int depth) {
        if (l == r) {
            return nullptr;
        }

        int mid = l + (r - l) / 2;

        nth_element(
            points.begin() + l,
            points.begin() + mid,
            points.begin() + r,
            [depth](const Point_KD& a, const Point_KD& b) {
                if (depth % 2 == 0) {
                    return a.x < b.x || (a.x == b.x && a.y < b.y);
                }
                else {
                    return a.y < b.y || (a.y == b.y && a.x < b.x);
                }
            });

        KDNode* node = new KDNode(points[mid]);

        node->left = build(points, l, mid, depth + 1);
        node->right = build(points, mid + 1, r, depth + 1);
        node->update_bbox();

        return node;
    }

    bool in_cone(const Point_KD& q, const Point_KD& p) {
        if (q.x < p.x - eps_KD) {
            return false;
        }

        if (q.y < p.y - eps_KD) {
            return false;
        }

        return (q.y - p.y) / (q.x - p.x + eps_KD) <= tg_KD + eps_KD;
    }

    bool in_cone(const BBox& bbox, const Point_KD& p) {
        if (bbox.x_max < p.x - eps_KD) {
            return false;
        }

        if (bbox.y_max < p.y - eps_KD) {
            return false;
        }

        return bbox.y_min - tg_KD * bbox.x_max <= p.y - tg_KD * p.x + eps_KD;
    }

    void search(KDNode* v, const Point_KD& p, const vector<Point_KD>& a, int d, double& best_dist, Point_KD& best_point) {
        if (!v || v->bbox.min_dist_to_point(p) >= best_dist - eps_KD || !in_cone(v->bbox, p)) {
            return;
        }

        double potential_best_dist = dist(a[v->point.index], a[p.index]);
        if (potential_best_dist > eps_KD && potential_best_dist < best_dist && in_cone(v->point, p)) {
            best_dist = potential_best_dist;
            best_point = v->point;
        }

        if (d % 2 == 0) {
            if (p.x > v->point.x) {
                search(v->right, p, a, d + 1, best_dist, best_point);
                search(v->left, p, a, d + 1, best_dist, best_point);
            }
            else {
                search(v->left, p, a, d + 1, best_dist, best_point);
                search(v->right, p, a, d + 1, best_dist, best_point);
            }
        }
        else {
            if (p.y > v->point.y) {
                search(v->right, p, a, d + 1, best_dist, best_point);
                search(v->left, p, a, d + 1, best_dist, best_point);
            }
            else {
                search(v->left, p, a, d + 1, best_dist, best_point);
                search(v->right, p, a, d + 1, best_dist, best_point);
            }
        }
    }
};

vector<tuple<double, int, int>> Get_KD(vector<Point_KD>& a) {
    vector<tuple<double, int, int>> EDGES;
  
    for (double ang : { 0.0, 60.0, 120.0, 180.0, 240.0, 300.0 }) {
        vector<Point_KD> b;
        for (int i = 0; i < (int)a.size(); i++) {
            Point_KD p = rotate(a[i], ang * PI / 180.0);
            p.index = i;
            b.push_back(p);
        }

        KDTree tree;
        tree.build(b);

        for (int i = 0; i < (int)a.size(); i++) {
            Point_KD cp = tree.Find_Nearest_In_Cone(b[i], a);
            if (cp.index != -1) {
                EDGES.push_back({ dist(a[i], a[cp.index]), i, cp.index });
            }
        }
    } sort(EDGES.begin(), EDGES.end());

    return EDGES;
}
