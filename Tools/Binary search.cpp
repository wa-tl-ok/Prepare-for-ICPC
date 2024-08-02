int bs_ll(vector<int>& arr, int target) {
    if (arr[0] >= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] >= target) {
            right = mid - 1;
        }
        else {
            if (arr[mid + 1] >= target) {
                return mid;
            }
            left = mid + 1;
        }
    }
    return left;
}

int bs_lr(vector<int>& arr, int target) {
    if (arr[arr.size() - 1] < target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}

int bs_rl(vector<int>& arr, int target) {
    if (arr[0] > target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > target) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return right;
}

int bs_rr(vector<int>& arr, int target) {
    if (arr[arr.size() - 1] <= target) {
        return -1;
    }
    int left = 0;
    int right = arr.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] <= target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return left;
}
