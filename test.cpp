/*
 * test.cpp
 * Copyright (C) 2014 mlckq <moon5ckq@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <cstdio>
#include "HighAccuracy.h"
#include "BITree.h"

int main(int argc, char **argv) {
    HighAccuracy _(123456789);
    //printf("%s\n", _.str().c_str());
    HighAccuracy a("12345678901234567890123456789");
    HighAccuracy b("1234567890123456789123456789");
    //printf("%s\n", a.str().c_str());
    a*= 1234;
    //printf("%s\n", a.str().c_str());
    /*
    a = 1;
    clock_t start = clock();
    for (int i = 2; i < 10000; ++i)
        a *= i;
    fprintf(stderr, "%lu %d\n", clock() - start, CLOCKS_PER_SEC);
    */
    printf("%s %s\n", a.str().c_str(), b.str().c_str());
    printf("%d\n", SimpleDiv(a, b));

    BITree t(10, 1);
    while (true) {
        char cmd[10];
        int x, y;
        scanf("%s %d %d", cmd, &x, &y);
        if (cmd[0] == 'Q') break;
        else if (cmd[0] == 'S') printf("sum = %d\n", t.sum(x, y));
        else if (cmd[0] == 'C') {
            printf("change\n");
            t.set(x, y);
        } else if (cmd[0] == 'K') printf("kth %d\n", t.getKth(x));
    }

    return 0;
}

