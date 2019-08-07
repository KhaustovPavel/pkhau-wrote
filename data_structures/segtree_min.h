#ifndef INCLUDE_SEGTREE_MIN_H_
#define INCLUDE_SEGTREE_MIN_H_

#include <vector>
#include <limits>

using std::vector;
using std::numeric_limits;

template <typename T>
class SegmentTreeMin {
 public:
    // Function for better customization
    inline T MinValue(T val1, T val2) {
        return min(val1, val2);
    }

    inline void Push(int v) {
        if (set_data[v] != -inf_value) {
            tree_data[v << 1] = tree_data[(v << 1) | 1] = set_data[v] + add_data[v];
            set_data[v << 1] = set_data[(v << 1) | 1] = set_data[v];
            add_data[v << 1] = add_data[(v << 1) | 1] = add_data[v];
            set_data[v] = -inf_value;
            add_data[v] = T{};
        } else {
            if (add_data[v] != T{}) {
                tree_data[v << 1] += add_data[v];
                tree_data[(v << 1) | 1] += add_data[v];
                add_data[v << 1] = add_data[(v << 1) | 1] = add_data[v];
                add_data[v] = T{};
            }
        }
    }

    T UpdateRange(int v, int tl, int tr, int l, int r, T new_val) {
        if (l > r) {
            return tree_data[v];
        }
        if (l == tl && tr == r) {
            set_data[v] = new_val;
            add_data[v] = T{};
            return tree_data[v] = new_val;
        } else {
            Push(v);
            int tm = (tl + tr) >> 1;
            T left_val = UpdateRange(v << 1, tl, tm, l, min(r, tm), new_val);
            T right_val = UpdateRange((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r, new_val);
            return tree_data[v] = MinValue(left_val, right_val);
        }
    }

    inline void UpdateRange(int l, int r, T new_val) {
        UpdateRange(1, 0, n - 1, l, r, new_val);
    }

    inline void Update(int ind, T new_val) {
        UpdateRange(1, 0, n - 1, ind, ind, new_val);
    }

    T AddRange(int v, int tl, int tr, int l, int r, T add_val) {
        if (l > r) {
            return tree_data[v];
        }
        if (l == tl && tr == r) {
            add_data[v] += add_val;
            tree_data[v] += add_val;
            return tree_data[v];
        } else {
            Push(v);
            int tm = (tl + tr) >> 1;
            T left_val = AddRange(v << 1, tl, tm, l, min(r, tm), add_val);
            T right_val = AddRange((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r, add_val);
            return tree_data[v] = MinValue(left_val, right_val);
        }
    }

    inline void AddRange(int l, int r, T add_val) {
        AddRange(1, 0, n - 1, l, r, add_val);
    }

    inline void Add(int ind, T add_val) {
        AddRange(1, 0, n - 1, ind, ind, add_val);
    }

    T GetMin(int v, int tl, int tr, int l, int r) {
        if (l > r) {
            return inf_value;
        }
        if (l == tl && r == tr) {
            return tree_data[v];
        }
        Push(v);
        int tm = (tl + tr) >> 1;
        return MinValue(GetMin(v << 1, tl, tm, l, min(r, tm)), GetMin((v << 1) | 1, tm + 1, tr, max(l, tm + 1), r));
    }

    inline T GetMin(int l, int r) {
        return GetMin(1, 0, n - 1, l, r);
    }

    inline void SetInf(T new_inf_value) {
        inf_value = new_inf_value;
    }

    inline void Assign(int new_n, T value) {
        n = new_n;
        tree_data.assign(n << 2, value);
        set_data.assign(n << 2, -inf_value);
        add_data.assign(n << 2, T{});
    }

    inline void Resize(int new_n) {
        n = new_n;
        tree_data.assign(n << 2, inf_value);
        set_data.assign(n << 2, -inf_value);
        add_data.assign(n << 2, T{});
    }

    inline void Clear() {
        n = 0;
        tree_data.clear();
        set_data.clear();
        add_data.clear();
    }

    inline SegmentTreeMin() {
        n = 0;
        SetInf(numeric_limits<T>::max());
    }

    inline SegmentTreeMin(int new_n) {
        SetInf(numeric_limits<T>::max());
        Resize(new_n);
    }

    inline SegmentTreeMin(int new_n, T init_value) {
        SetInf(numeric_limits<T>::max());
        Assign(new_n, init_value);
    }

    int n;
    T inf_value;
    vector<T> tree_data;
    vector<T> set_data;
    vector<T> add_data;
};

#endif // INCLUDE_SEGTREE_MIN_H_
