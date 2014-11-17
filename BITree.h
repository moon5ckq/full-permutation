/*
 * BITree.h
 * Copyright (C) 2014 mlckq <moon5ckq@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef BITREE_H
#define BITREE_H

#include <vector>

class BITree {
public:
    BITree(int size = 0, int value = 0);
    void reset(int size = 0, int value = 0);
    int sum(int l, int r) const;
    int getKth(int k) const;
    void set(int k, int value);
    inline int size() const {
        return static_cast<int>(_s.size() - 1);
    }
    inline int operator[] (int index) const {
        return _v[index];
    }
    
private:
    std::vector<int> _s, _v;
    int _depth;
    int _sum(int m) const;
};

#endif /* !BITREE_H */
