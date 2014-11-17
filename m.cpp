/*
 * m1.cpp
 * Copyright (C) 2014  <moon5ckq@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <cstdio>
#include <string>
#include <vector>
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
    vector<int> p = read(argv[2]), p_;
    int n = static_cast<int>(p.size());
    p_.resize(n);
    HighAccuracy k;
    if (argc >= 3)
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
    for (int i = n - 1; i >= 0; --i) {
        int c = SimpleDiv(x, fact);
        x -= fact * c;
        if (i) fact /= i;
        p_[i] = t.getKth(c + 1);
        t.set(p_[i], 0);
    }

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
    } else if (string(argv[1]) == "3") {
    } else if (string(argv[1]) == "4") {
    } else {
        printf("type: 1,2,3,4\n");
        return 0;
    }

    return 0;
}
