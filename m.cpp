/*
 * m.cpp
 * Copyright (C) 2014 mlckq <moon5ckq@gmail.com>, xxr <xxr3376@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
#include "HighAccuracy.h"
#include "BITree.h"
using std::string;
using std::vector;

vector<int> read(const char* path) {
    vector<int> ret;
    FILE* fin = fopen(path, "r");
    for (int x; fscanf(fin, "%d", &x) != EOF;)
        ret.push_back(x);
    std::reverse(ret.begin(), ret.end());
    return ret;
}

void m1(int argc, char **argv) {
    vector<int> p = read(argv[2]), p_, q;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    q.resize(n);
    HighAccuracy k;
    if (argc > 3)
        k.load(argv[3]);
    else
        k = 1;

    //step1
    HighAccuracy fact(1), m(0);
    BITree t(n, 0);
    for (int i = 0; i < n; ++i) {
        if (i) fact *= i;
        m += fact * t.sum(1, p[i]);
        t.set(p[i], 1);
    }
    //step 2
    HighAccuracy x = m + k;
    //step 3
    t.reset(n, 1);
    for (int i = 0; i < n; ++i)
        q[i] = x.div(i+1);
    for (int i = n - 1; i >= 0; --i) {
        p_[i] = t.getKth(q[i] + 1);
        t.set(p_[i], 0);
    }

    for (int i = n - 1; i >= 0; --i)
        printf("%d ", p_[i]);
    puts("");
}

void m2(int argc, char **argv) {
    vector<int> p = read(argv[2]),q, p_;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    q.resize(n);
    HighAccuracy k;
    if (argc > 3)
        k.load(argv[3]);
    else
        k = 1;
    
    //step 1
    for (int i = 0; i < n; ++i)
        q[p[i] - 1] = i + 1;
    HighAccuracy m(0), fact(1);
    BITree t(n, 0);
    for (int i = n - 1; i >0; --i) {
        fact *= i;
        m = m * (i + 1) + (q[i] - t.sum(1, q[i]) - 1);
        t.set(q[i], 1);
    }
    //step 2
    HighAccuracy x = m + k;
    //step 3
    t.reset(n, 1);
    for (int i = 0; i < n; ++i)
        q[i] = x.div(i+1);
    for (int i = n - 1; i >= 0; --i) {
        int y = t.getKth(q[i] + 1);
        p_[y - 1] = i + 1;
        t.set(y, 0);
    }

    for (int i = n - 1; i >= 0; --i)
        printf("%d ", p_[i]);
    puts("");
}

void m3(int argc, char **argv) {
    vector<int> p = read(argv[2]),q, p_;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    q.resize(n);
    HighAccuracy k;
    if (argc > 3)
        k.load(argv[3]);
    else
        k = 1;
    
    //step 1
    for (int i = 0; i < n; ++i)
        q[p[i] - 1] = i + 1;
    HighAccuracy m(0), fact(1);
    BITree t(n, 0);
    for (int i = n - 1; i >0; --i) {
        fact *= i;
        p[i] = q[i] - t.sum(1, q[i]) - 1;
        t.set(q[i], 1);
    }
    for (int i = 1; i < n; ++i)
        m = m * (i + 1) + p[i];
    //step 2
    HighAccuracy x = m + k;
    //step 3
    t.reset(n, 1);
    for (int i = n; i > 0; --i) {
        int c = x.div(i);
        int y = t.getKth(c + 1);
        p_[y - 1] = i;
        t.set(y, 0);
    }
    
    for (int i = n - 1; i >= 0; --i)
        printf("%d ", p_[i]);
    puts("");
}

void m4(int argc, char **argv) {
    vector<int> p = read(argv[2]), q, p_;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    q.resize(n);
    HighAccuracy k;
    if (argc > 3)
        k.load(argv[3]);
    else
        k = 1;

    //step 1
    for (int i = 0; i < n; ++i)
        q[p[i] - 1] = i + 1;
    BITree t(n, 0);
    HighAccuracy m(0);
    t.set(q[0], 1);
    for (int i = 1, tmp = 0; i < n; ++i) {
      int cur = (tmp&1) ?
          t.sum(q[i] + 1, n) :
          t.sum(1, q[i] - 1);

      if (i&1) tmp = cur;
      else tmp += cur;

      m = m * (i + 1) + cur;
      t.set(q[i], 1);
    }
    //step 2
    HighAccuracy x = m + k;
    //step 3
    for (int i = n; i > 1; --i) {
        q[i - 1] = x.div(i);
    }
    //step 4
    t.reset(n, 1); //right
    BITree t_reverse(n, 1); //left

    for (int i = n - 1; i > 0; --i) {
      int cur = 0;
      if (i == 1)
          cur = 0;
      else if (i & 1)
          cur = q[i-1] + q[i - 2];
      else
          cur = q[i-1];

      int r;
      if (cur & 1)
          r = n - t_reverse.getKth(q[i] + 1);
      else
          r = t.getKth(q[i] + 1) - 1;

      t.set(r+1, 0);
      t_reverse.set(n - r, 0);

      p_[r] = i + 1;
    }

    // put 1 back
    p_[t.getKth(1) - 1] = 1;

    for (int i = n - 1; i >= 0; --i)
        printf("%d ", p_[i]);
    puts("");
}

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("usage: %s <type> <input permutation> [next]\n", argv[0]);
        return 0;
    }

    if (string(argv[1]) == "1") {
        m1(argc, argv);
    } else if (string(argv[1]) == "2") {
        m2(argc, argv);
    } else if (string(argv[1]) == "3") {
        m3(argc, argv);
    } else if (string(argv[1]) == "4") {
        m4(argc, argv);
    } else {
        printf("type: 1,2,3,4\n");
        return 0;
    }

    return 0;
}
