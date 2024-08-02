class Heap_min {
public:
    Heap_min(int capacity) : capacity(capacity), size(0) {
        array = new int[capacity];
    }

    ~Heap_min() {
        delete[] array;
    }

    void insert(int value) {
        if (size == capacity) {
            return;
        }
        int i = size++;
        array[i] = value;

        while (i != 0 && array[(i - 1) / 2] > array[i]) {
            swap(array[i], array[(i - 1) / 2]);
            i = (i - 1) / 2;
        }
    }

    void deleteMin() {
        if (size != 0) {
            array[0] = array[--size];
            heapify(0);
        }
    }

    int Min() const {
        if (size != 0) {
            return array[0];
        }
        else {
            return -1;
        }
    }

    void clear() {
        size = 0;
    }

private:
    int* array;
    int capacity;
    int size;

    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    void heapify(int i) {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && array[left] < array[smallest])
            smallest = left;

        if (right < size && array[right] < array[smallest])
            smallest = right;

        if (smallest != i) {
            swap(array[i], array[smallest]);
            heapify(smallest);
        }
    }
};
