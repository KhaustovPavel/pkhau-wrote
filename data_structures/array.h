#ifndef INCLUDE_ARRAY_H_
#define INCLUDE_ARRAY_H_

#include <vector>
#include <limits>

using std::vector;
using std::numeric_limits;

template <typename T>
class Array {
 public:
    // Function for better customization
    inline T MinValue(T val1, T val2) {
        return min(val1, val2);
    }

    inline void UpdateRange(int l, int r, T new_val) {
        for (int i = l; i <= r; ++i) {
            data[i] = new_val;
        }
    }

    inline void Update(int ind, T new_val) {
        data[ind] = new_val;
    }

    inline void AddRange(int l, int r, T add_val) {
        for (int i = l; i <= r; ++i) {
            data[i] += add_val;
        }
    }

    inline void Add(int ind, T add_val) {
        data[ind] += add_val;
    }

    inline T GetMin(int l, int r) {
        T res = data[l];
        for (int i = l + 1; i <= r; ++i) {
            res = MinValue(res, data[i]);
        }
        return res;
    }

    inline T GetSum(int l, int r) {
        T res = data[l];
        for (int i = l + 1; i <= r; ++i) {
            res += data[i];
        }
        return res;
    }

    inline void SetInf(T new_inf_value) {
        inf_value = new_inf_value;
    }

    inline void Assign(int new_n, T value) {
        n = new_n;
        data.assign(n, value);
    }

    inline void Resize(int new_n) {
        n = new_n;
        data.assign(n, inf_value);
    }

    inline void Clear() {
        n = 0;
        data.clear();
    }

    inline Array() {
        n = 0;
        SetInf(numeric_limits<T>::max());
    }

    inline Array(int new_n) {
        SetInf(numeric_limits<T>::max());
        Resize(new_n);
    }

    inline Array(int new_n, T init_value) {
        SetInf(numeric_limits<T>::max());
        Assign(new_n, init_value);
    }

    int n;
    T inf_value;
    vector<T> data;
};

#endif // INCLUDE_ARRAY_H_
