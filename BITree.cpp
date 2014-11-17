/*
 * BITree.cpp
 * Copyright (C) 2014 mlckq <moon5ckq@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include "BITree.h"

#define LOWBIT(x) ((x)&-(x))

BITree::BITree(int size /*= 0*/, int value /*= 0*/) {
    reset(size, value);
}

void BITree::reset(int size /*= 0*/, int value /*= 0*/) {
    _s.resize(size + 1);
    _v.resize(size + 1);
    for (int i = 1; i <= size; ++i) {
        _s[i] = LOWBIT(i) * value;
        _v[i] = value;
    }
    for (_depth = 0; (1 << (1 + _depth)) <= size; _depth ++);
}

void BITree::set(int k, int value) {
    int n = size();
    int delta = value - _v[k];
    _v[k] = value;
    for (int i = k; i <= n; i += LOWBIT(i))
        _s[i] += delta;
}

int BITree::_sum(int m) const {
    int ret = 0;
    for (int i = m; i; i -= LOWBIT(i))
        ret += _s[i];
    return ret;
}

int BITree::sum(int l, int r) const {
    return _sum(r) - _sum(l - 1);
}

int BITree::getKth(int k) const {
    int m = 0, n = size();
    k += 1;
    for (int i = (1 << _depth); i; i >>= 1) {
        if (m + i <= n && _s[m + i] < k) {
            m += i;
            k -= _s[m];
        }
    }
    while (m && _v[m] == 0)
        --m;
    return m;
}
