#ifndef INCLUDE_FENWICK_SUM_H_
#define INCLUDE_FENWICK_SUM_H_

#include <vector>

using std::vector;

template <typename T>
class FenwickSum {
 public:
    inline FenwickSum() {
        n = 0;
    }

    inline FenwickSum(int new_n) {
        Resize(new_n);
    }

    inline FenwickSum(int new_n, T value) {
        Assign(new_n, value);
    }

    inline FenwickSum(vector<T>& new_data) {
        Init(new_data);
    }

    inline void Resize(int new_n) {
        n = new_n;
        data.resize(n);
    }

    inline void Assign(int new_n, T value) {
        n = new_n;
        data.assign(n, value);
    }

    inline void Init(vector<T>& new_data) {
        data = new_data;
        n = static_cast<int>(data.size());
    }

    inline void Reset() {
        Clear();
        Resize(n);
    }

    inline void Clear() {
        n = 0;
        data.clear();
    }

    inline void Add(int index, T value) {
        for (; index < n; index |= (index + 1)) {
            data[index] += value;
        }
    }

    inline void Set(int index, T value) {
        Add(index, -GetSum(index, index));
        Add(index, value);
    }

    inline T GetSum(int index) {
        T res{};
        for (; index >= 0; index = (index & (index + 1)) - 1) {
            res += data[index];
        }
        return res;
    }

    inline T GetSum(int l_index, int r_index) {
        return GetSum(r_index) - GetSum(l_index - 1);
    }

    int n;
    vector<T> data;
};

#endif // INCLUDE_FENWICK_SUM_H_
