long long mergeinverse(vector <long long>& a) {
    long long inv_count = 0;
    if (a.size() > 1) {
        long long mid = a.size() / 2;

        vector<long long> left(a.begin(), a.begin() + mid);
        vector<long long> right(a.begin() + mid, a.end());

        inv_count += mergeinverse(left);
        inv_count += mergeinverse(right);

        long long i = 0, j = 0, k = 0;

        while (i < left.size() && j < right.size()) {
            if (left[i] <= right[j]) {
                a[k] = left[i];
                i++;
            }
            else {
                a[k] = right[j];
                j++;
                inv_count += (long long)left.size() - i;
            }
            k++;
        }
        while (i < left.size()) {
            a[k] = left[i];
            i++;
            k++;
        }
        while (j < right.size()) {
            a[k] = right[j];
            j++;
            k++;
        }
    }
    return inv_count;
}
